#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

#define MIUBRR (F_CPU/16/BAUD-1)

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init()
{

  UBRR0H = (MIUBRR >> 8);
  UBRR0L = (MIUBRR);

  UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0); // enables transfer and read + read interrupts
}

int uart_putchar(char c, FILE *stream)
{
  if(c == '\n')
  {
    uart_putchar('\r', stream);
  }

  loop_until_bit_is_set(UCSR0A, UDRE0);

  UDR0 = c;

  return c;
}

char uart_readchar()
{
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}
