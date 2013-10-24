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
int message3 = 0;
int first_time = 1;
void timer1_int_handler() {
    //unsigned int result;

   

    //message3++;

    //if (message3 == 10)
    //{
    #if ENABLE_UART_TX
       // message3 = 0;
        //PIE1bits.TXIE = 1;
    #endif
    #if ENABLE_I2C
    //if(first_time == 1)
    //{
        //unsigned char data1[4];
        //data1[0] = 0x32; //laser type = 0x32 .. infrared = 0x42
    //   i2c_master_send(1,data1);

     
            i2c_master_recv(6);
           // first_time = 0;
        //}
    #endif
    //}


    //WriteTimer1(65086);

  
}

int ADCValue = 0;
//int x[300];
int counter2 = 0;
char testbuffer[50];



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