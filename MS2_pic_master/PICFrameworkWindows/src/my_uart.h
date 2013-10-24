#ifndef __my_uart_h
#define __my_uart_h

#include "messages.h"

#define MAXUARTBUF 6
#if (MAXUARTBUF > MSGLEN)
#define MAXUARTBUF MSGLEN
#endif
typedef struct __uart_comm {
	unsigned char buffer[MAXUARTBUF];
	unsigned char	buflen;
        unsigned char inbuffer[MAXUARTBUF];
        unsigned char inbuflen;
        unsigned char status;
        unsigned char bufind;
} uart_comm;

void init_uart_recv(uart_comm *);
void uart_recv_int_handler(void);
void putIntoUARTBuffer( unsigned char *buffer);

#endif
