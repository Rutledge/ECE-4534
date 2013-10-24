#include "maindefs.h"
#include <stdio.h>
#include "uart_thread.h"

// This is a "logical" thread that processes messages from the UART
// It is not a "real" thread because there is only the single main thread
// of execution on the PIC because we are not using an RTOS.

int uart_lthread(uart_thread_struct *uptr, int msgtype, int length, unsigned char *msgbuffer) {
    if (msgtype == MSGT_OVERRUN) {
    }
    else if (msgtype == MSGT_UART_DATA) {
        if (msgbuffer[0] == LASER_DATA_TO_ARM)
    }
}