#include <xdc/std.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>

#include <ti/ipc/Ipc.h>
#include <ti/ipc/MultiProc.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/syslink/SysLink.h>

#include "log.h"
#include "message_loop.h"

Void message_loop_fun(UArg arg0, UArg arg1) {
    Int         status = 0;
    Error_Block eb;
    UInt16      proc_id;
    Bool        running = TRUE;
    UInt        loop = 0;

    LOG_INFO("--> message_loop_fun:");

    Error_init(&eb);

    while (running) {
        do {
            status = Ipc_start();
        } while (status == Ipc_E_NOTREADY);

        if (status < 0) {
            LOG_FATAL("Ipc_start error=%d", (IArg)status);
            goto leave;
        }

        proc_id = MultiProc_getId("HOST");

        do {
            loop++;
            status = Ipc_attach(proc_id);

            if ((status == Ipc_E_NOTREADY) && ((loop & 0xFFF) == 0)) {
                //Task_sleep(1);
            }
        } while (status == Ipc_E_NOTREADY);

        if (status < 0) {
            LOG_FATAL("Ipc_attach error=%d", (IArg)status);
            goto leave;
        }

        MessageLoop *msg_loop = message_loop_new();
        message_loop_start(msg_loop);
        message_loop_destroy(msg_loop);

        do {
            status = Ipc_detach(proc_id);

            if ((status == Ipc_E_NOTREADY) && ((++loop & 0xFFF) == 0)) {
                //Task_sleep(1);
            }
        } while (status == Ipc_E_NOTREADY);

        if (status < 0) {
            LOG_FATAL("Ipc_detach error=%d", (IArg)status);
            goto leave;
        }

        Ipc_stop();
    } 

leave:
    LOG_INFO("<-- message_loop_fun: %d", (IArg)status);
    return;
}

Int main(Int argc, Char* argv[]) {
    LOG_INIT();

    LOG_INFO("--> main:");

    Error_Block eb;
    Task_Params taskParams;
    Error_init(&eb);

    Task_Params_init(&taskParams);
    taskParams.instance->name = "message_loop_fun";
    taskParams.arg0 = (UArg)argc;
    taskParams.arg1 = (UArg)argv;
    taskParams.stackSize = 0x1000;
    Task_create(message_loop_fun, &taskParams, &eb); /* 启动 message 线程 */

    if (Error_check(&eb)) 
        LOG_FATAL("failed to create application startup thread");

    BIOS_start();

    LOG_INFO("<-- main:");
    return (0);
}
