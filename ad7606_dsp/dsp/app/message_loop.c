#include <stdlib.h>
#include <string.h>

#include <ti/syslink/Std.h>
#include <ti/ipc/MessageQ.h>

#include "message_heap.h"
#include "ad_workshop.h"
#include "log.h"
#include "../shared/protocol.h"
#include "ring_buffer.h"
#include "message_loop.h"
#include "ipc_ring_buffer.h"

struct _MessageLoop {
    MessageQ_Handle queue;
    int quit;
    int is_started;

    ad7606 *ad;
    ADWorkshop *shop;
    MessageHeap *heap;
    RingBuffer *buffer;
    MessageQ_QueueId reply_id;
};

MessageLoop *message_loop_new() {
    MessageLoop *loop = (MessageLoop *)malloc(sizeof(MessageLoop)); 
    memset(loop, sizeof(MessageLoop), 0);

    MessageQ_Params params;
    MessageQ_Params_init(&params);
    loop->queue = MessageQ_create(MSG_QUEUE_NAME_SLAVE, &params);
    loop->heap = message_heap_new(SHARED_REGION_ID_MSG_QUEUE);

    loop->quit = false;
    loop->is_started = false;

    return loop;
}

void message_loop_destroy(MessageLoop *loop) {
    if (! loop)
        return;

    if (loop->shop)
        ad_workshop_destroy(loop->shop);

    MessageQ_delete(&loop->queue);
    message_heap_destroy(loop->heap);
    ring_buffer_destroy(loop->buffer);
    free(loop);
}

/* 当 AD7606 驱动触发 trigger 事件时候将进行回调 */
static void message_loop_on_ad_trigger(float *data, unsigned int count, void *user_data) {
    MessageLoop *loop = (MessageLoop *)user_data;
    ad_workshop_import(loop->shop, data, count);
}

/* start 命令处理函数 */
static void message_loop_on_start(MessageLoop *loop, Message *msg) {
    if (loop->is_started) {
        LOG_WARN("already recv start cmd");
        return;
    }

    LOG_INFO("start, sample rate is %d points", msg->rate);

    /* 保存HOST 端 MessageQ ID */
    loop->reply_id = MessageQ_getReplyQueue(msg); 

    loop->buffer = ipc_ring_buffer_new(RING_BUFFER_NAME);
    loop->ad = ad7606_new(5 /* range */, loop->buffer);
    loop->shop = ad_workshop_new(loop->buffer, loop->reply_id, message_heap_id(loop->heap));

    /* 设置回调事件 */
    ad7606_trigger(loop->ad, msg->trigger, message_loop_on_ad_trigger, loop);
    LOG_DEBUG("channel is %d", msg->channel);
    ad7606_set_channel(loop->ad, msg->channel);
    ad7606_start(loop->ad, msg->rate);

    loop->is_started = true;
}

/* enable FFT 命令处理函数 */
static void message_loop_on_enable_fft(MessageLoop *loop, Message *msg) {
    LOG_INFO("recv enable fft");
    if (! loop->is_started)
        LOG_WARN("no start cmd previous");
    else 
        ad_workshop_do_fft(loop->shop, true); /* 对后续的数据进行要 FFT 运算 */
}

/* disable FFT 命令处理函数 */
static void message_loop_on_disable_fft(MessageLoop *loop, Message *msg) {
    LOG_INFO("recv disable fft");
    if (! loop->is_started)
        LOG_WARN("no start cmd previous");
    else 
        ad_workshop_do_fft(loop->shop, false); /* 不需要对数据进行 FFT 运算 */
}

/* 设置采样率命令处理函数 */
static void message_loop_on_sample_rate(MessageLoop *loop, Message *msg) {
    LOG_INFO("recv change sample rate");
    if (! loop->is_started)
        LOG_WARN("no start cmd previous");
    else 
        ad7606_start(loop->ad, msg->rate); /* 设置新的采样率并重新启动 AD */
}

void message_loop_start(MessageLoop *loop) {
    ASSERT(loop);
    LOG_INFO("message loop start");

    loop->quit = false;
    while (! loop->quit) {
        LOG_INFO("wait for cmd");
        Message *msg; /* 阻塞在这里，等待 host 端命令 */
        MessageQ_get(loop->queue, (MessageQ_Msg *)&msg, MessageQ_FOREVER);

        switch (msg->cmd) {
            case MSG_CMD_START:
                message_loop_on_start(loop, msg);
                break;

            case MSG_CMD_STOP:
                ad7606_stop(loop->ad);
                loop->quit = true;
                break;

            case MSG_CMD_SAMPLE_RATE:
                message_loop_on_sample_rate(loop, msg);
                break;

            case MSG_CMD_ENABLE_FFT:
                message_loop_on_enable_fft(loop, msg);
                break;

            case MSG_CMD_DISABLE_FFT:
                message_loop_on_disable_fft(loop, msg);
                break;

            default:
                LOG_FATAL("recv unexpected cmd");
                break;
        }

        MessageQ_free((MessageQ_Msg)msg);
    }
    loop->quit = true;

    LOG_INFO("message loop end");
}

void message_loop_stop(MessageLoop *loop) {
    ASSERT(loop);
    loop->quit = true;
}
