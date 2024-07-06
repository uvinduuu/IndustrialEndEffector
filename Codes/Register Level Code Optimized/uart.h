#ifndef UART            
#define UART

#include <avr/io.h>

unsigned char USART_Receive();
void UART_Txchar(char ch);
void trans_string(char str[]);
void trans_num(uint16_t num);
void init_uart();

#endif