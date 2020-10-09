#ifndef _UART_H
#define _UART_H
#include <stdio.h>


void uart_init();
int uart_putchar(char c, FILE *stream);
char uart_readchar();

extern FILE uart_output;

#endif
