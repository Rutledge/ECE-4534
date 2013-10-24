// This is where the "user" interrupts handlers should go
// The *must* be declared in "user_interrupts.h"

#include "maindefs.h"
#ifndef __XC8
#include <timers.h>
#else
#include <plib/timers.h>
#endif
#include "user_interrupts.h"
#include "messages.h"

unsigned char msgbuffer[MSGLEN + 1];
unsigned char msgtype;

// A function called by the interrupt handler
// This one does the action I wanted for this program on a timer0 interrupt

void timer0_int_handler() {
    unsigned int val;
    int length, msgtype;

    // toggle an LED
    LATBbits.LATB0 = !LATBbits.LATB0;
    // reset the timer
    WriteTimer0(0);
    // try to receive a message and, if we get one, echo it back
    length = FromMainHigh_recvmsg(sizeof(val), (unsigned char *)&msgtype, (void *) &val);
    if (length == sizeof (val)) {
        ToMainHigh_sendmsg(sizeof (val), MSGT_TIMER0, (void *) &val);
    }
}

// A function called by the interrupt handler
// This one does the action I wanted for this program on a timer1 interrupt

void timer1_int_handler() {
    //unsigned int result;

    // read the timer and then send an empty message to main()
 /*   LATBbits.LATB1 = !LATBbits.LATB1;
    result = ReadTimer1();
    ToMainLow_sendmsg(0, MSGT_TIMER1, (void *) 0);*/

 //   ConvertADC();
     // reset the timer
    ToMainLow_sendmsg(0, MSGT_TIMER1, (void *) 0);


    WriteTimer1(65086);

  
}

int ADCValue = 0;
//int x[300];
int counter2 = 0;
char testbuffer = 0;

void uart_rx_int_handler()
{
    testbuffer = ReadUSART();
    ToMainHigh_sendmsg(1, MSGT_I2C_DATA, (void *)testbuffer);



}

void uart_tx_int_handler()
{
    FromMainHigh_recvmsg(MSGLEN, &msgtype, (void *) msgbuffer);

        WriteUSART(msgbuffer[0]);

       // TXREG = 0x55;
        PIE1bits.TXIE = 0;
}

void adc_int_handler() {

    ADCValue = ReadADC();




//    x[counter2] = ADCValue;

    if(counter2 < 299)
    counter2++;
    else
    {
        counter2 = 0;
        CloseTimer1();
//        ToMainHigh_sendmsg()
    }

}