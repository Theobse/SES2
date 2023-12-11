/*
 * uart.h
 *
 *  Created on: 03-Dec-2017
 *      Author: defaultuser0
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include <stdlib.h>
#include "circbuf.h"
#include "project3.h"

#define BAUD 115200
#define BAUD_RATE ((SystemCoreClock)/((BAUD)*(16)))



typedef enum{
	TX_SUCCESS=6,
	RX_SUCCESS=7,
	TX_IRQ=8,
	RX_IRQ=9,
	UART_CONFIG_SUCCESS
}UART_status;


extern uint8_t log_mode;

UART_status UART_configure();
UART_status UART_send(uint8_t *data0);
UART_status UART_send_n(uint8_t *data0, uint8_t length);
UART_status UART_receive(uint8_t *data0);
UART_status UART_receive_n(uint8_t *data0, uint8_t length);
UART_status UART0_IRQHandler(void);

#endif /* SOURCES_UART_H_ */
