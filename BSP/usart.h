#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "sys.h"

void debug_uart_init(uint32_t bound);
void uart2_init(uint32_t bound);
void uart3_init(uint32_t bound);

#endif

