#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <ti/sysbios/knl/Queue.h>

typedef struct _Queue Queue;

Queue      * queue_new();
void         queue_destroy(Queue *queue);

void         queue_push(Queue *queue, Queue_Elem *elm);

/*
 * 出队，队列为空时会阻塞
 */
Queue_Elem * queue_pop(Queue *queue);

#endif
