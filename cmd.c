
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "uart.h"
#include "cmd.h"

char prompt[] = "prompt> ";
volatile bool line_done = false;
uint8_t line_index = 0;
volatile char lastest_c;

// interupts when new data on rx line
ISR(USART_RX_vect)
{
  char c = UDR0;
  lastest_c = c;
  if(line_done)
    return;

  uart_putchar(c, NULL); // prints back the character sent
  //printf("%02x", c);   // prints the hex value of character receved

  if(line_index < 247) // one smaller than 248 to save space for null byte (BUG - if at max then can't deleate characters)
  {
    if(c == 0x7f)
    {
      if(line_index > 0){
        line_index--;
        printf("\b \b"); //  \b is backspace (dosent delete only moves back, thats why theres a space(\x20))
      }
    }
    else
    {
      line[line_index++] = c;
    }
  }

  if(c == '\n')
  {
      line[line_index] = '\0';
      line_done = true;
      line_index = 0;

      // do my interpretation here?


  }
}


void move_cursor(enum directions dir)
{
    switch (dir)
    {
      case UP:
        uart_putchar(0x1b, NULL);
        uart_putchar(0x5b, NULL);
        uart_putchar(0x41, NULL);
        break;
      case DOWN:
        uart_putchar(0x1b, NULL);
        uart_putchar(0x5b, NULL);
        uart_putchar(0x42, NULL);
        break;
      case RIGHT:
        uart_putchar(0x1b, NULL);
        uart_putchar(0x5b, NULL);
        uart_putchar(0x43, NULL);
        break;
      case LEFT:
        uart_putchar(0x1b, NULL);
        uart_putchar(0x5b, NULL);
        uart_putchar(0x44, NULL);
        break;
    }
}

void cmd_init()
{
  stdout = &uart_output; // gives the ability to use printf
  //fputs(prompt, stdout); // prints the first "prompt>"

}
