#include "maindefs.h"
#include <stdio.h>
#include "messages.h"
#include "timer1_thread.h"

void init_timer1_lthread(timer1_thread_struct *tptr) {
    tptr->msgcount = 0;


}

// This is a "logical" thread that processes messages from TIMER1
// It is not a "real" thread because there is only the single main thread
// of execution on the PIC because we are not using an RTOS.

unsigned int message = 0;
int test = 0;

int timer1_lthread(timer1_thread_struct *tptr, int msgtype, int length, unsigned char *msgbuffer) {
    signed char retval;

   // tptr->msgcount++;
 /*   if (test)
    {
        message = 0x55;
        test = 0;
    }
    else
    {
        message = 0x08;
        test = 1;
    }*/
    message++;
    if (message == 1000)
    {       
    StartI2C();
    message = 0;
    }
    if(message%100 ==5)
    {
   //     PIE1bits.TXIE = 1;
    }


    

 //   FromMainHigh_sendmsg(sizeof (message), MSGT_MAIN1, (void *) &(message));
    //enable USART SEND
 //   PIE1bits.TXIE = 1;


    // Every tenth message we get from timer1 we
    // send something to the High Priority Interrupt
   /*/ if ((tptr->msgcount % 10) == 9) {
        retval = FromMainHigh_sendmsg(sizeof (tptr->msgcount), MSGT_MAIN1, (void *) &(tptr->msgcount));
        if (retval < 0) {
            // We would handle the error here
        }
    }*/
}