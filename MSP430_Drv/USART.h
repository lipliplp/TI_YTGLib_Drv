#ifndef __USART_H__
#define __USART_H__

#include "msp430.h"
#include "stdio.h"

void send_buf(unsigned char *ptr);    //·¢ËÍ×Ö·û´®
void USART_Init(void);
void uart_putchar(unsigned char dat);

#endif
