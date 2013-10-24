#include "maindefs.h"
#ifndef __XC8
#include <usart.h>
#else
#include <plib/usart.h>
#endif
#include "my_uart.h"

static uart_comm *uc_ptr;

void uart_recv_int_handler() {
    if (DataRdyUSART()) {
        uc_ptr->inbuffer[uc_ptr->inbuflen] = ReadUSART();
        uc_ptr->inbuflen++;
        // check if a message should be sent
        if (uc_ptr->inbuflen == 3) {
            ToMainLow_sendmsg(uc_ptr->inbuflen, MSGT_MOTOR_CONTROLS_FROM_ARM, (void *) uc_ptr->inbuffer);
            uc_ptr->inbuflen = 0;
        }
    }
    if (USART_Status.OVERRUN_ERROR == 1) {
        // we've overrun the USART and must reset
        // send an error message for this
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
        ToMainLow_sendmsg(0, MSGT_OVERRUN, (void *) 0);
    }
    #if ENABLE_GPIO
         MAIN_THREAD = 1;
         UART_RECEIVE_THREAD = 0;
    #endif
}
char testbuffer3;
char testbuffer4;
char testbuffer5;
char testbuffer6;

void putIntoUARTBuffer( unsigned char *buffer)
{

    /*if(buffer[0] == 0x42)
        uc_ptr->status = INFRARED_DATA_TO_ARM;
    else if (buffer[0] == 0x32)
        uc_ptr->status = LASER_DATA_TO_ARM;*/

    uc_ptr->buffer[0] = buffer[0];
    uc_ptr->buffer[1] = buffer[1];
    uc_ptr->buffer[2] = buffer[2];
    uc_ptr->buffer[3] = buffer[3];
    uc_ptr->buffer[4] = buffer[4];
    uc_ptr->buffer[5] = buffer[5];
    uc_ptr->buflen = 6;
    uc_ptr->bufind = 0;


}

char count = 0;
char bufferForUART[4];

void uart_tx_int_handler()
{

    #if ENABLE_GPIO
        MAIN_THREAD = 0;
        UART_TRANSMIT_THREAD = 1;
    #endif
    TXREG = uc_ptr->buffer[uc_ptr->bufind];
    char testbuffer = uc_ptr->buffer[uc_ptr->bufind];
    uc_ptr->bufind++;
    if(uc_ptr->bufind < uc_ptr->buflen)
    {
        PIE1bits.TXIE = 1;
    }
    #if ENABLE_GPIO
        MAIN_THREAD = 1;
        UART_TRANSMIT_THREAD = 0;
    #endif

/*
    //this will be called when we either have laser or infrared data to send
    if(uc_ptr->status == INFRARED_DATA_TO_ARM)
    {
    uc_ptr->buffer[0] = INFRARED_DATA_TO_ARM;
    /*uc_ptr->buffer[1] = count; //infra1
    uc_ptr->buffer[2] = count+1; //infra2
    uc_ptr->buffer[3] = count+2; //infra3
    uc_ptr->status = LASER_DATA_TO_ARM;
    ToMainHigh_sendmsg(4, MSGT_SEND_SENSOR_DATA_TO_ARM, uc_ptr->buffer);
    count = count+3;
    }
    else
    {
    uc_ptr->buffer[0] = LASER_DATA_TO_ARM;
    
    uc_ptr->buffer[1] = count; //las1
    uc_ptr->buffer[2] = count+1; //las2
    uc_ptr->status = INFRARED_DATA_TO_ARM;
    ToMainHigh_sendmsg(3, MSGT_SEND_SENSOR_DATA_TO_ARM, uc_ptr->buffer);
    count = count+2;
    }
    
    bufferForUART[0] = count;
    bufferForUART[1] = count+1;
    bufferForUART[2] = count+2;
    bufferForUART[3] = count+3;*/
    //ToMainHigh_sendmsg(4, MSGT_I2C_SENSOR, uc_ptr->buffer);*/


}

void init_uart_recv(uart_comm *uc) {
    uc_ptr = uc;
    uc_ptr->buflen = 0;
    uc_ptr->inbuflen = 0;
    uc_ptr->status = INFRARED_DATA_TO_ARM;
}

/*char bufferFromUART[50];
char count2 = 0;

void uart_rx_int_handler()
{
    bufferFromUART[count2] = ReadUSART();
    count2++;
    if (count2 == 50)
    {
        count2 = 0;
    }
    

}*/

