/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file uart.h
 * @brief This header file includes UART functions
 * @date October 24, 2017
 *
 * long description - The uart.h file includes function declarations to -
 *                      1) configure UART (UART_Configure())
 *                      2) send a UART character (UART_send())
 *                      3) send n UART characters (UART_send_n())
 *                      4) receive UART character (UART_receive())
 *                      5) receive n UART characters (UART_receive_n())
 *                      6) handle UART interrupts (UART0_IRQHandler())
 *
 *
 ***************************************************************************************************/

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_

/*----- Header-Files -------------------------------------------------------*/

#include "MKL25Z4.h"
#include "circbuf.h"
#include "conversion.h"

/*----- Extern Declarations -------------------------------------------------------*/

extern uint8_t Rx_Data;
extern uint8_t Tx_Data;
extern CB_t Tx_Buffer;
extern CB_t Rx_Buffer;

/*----- Macros for baud rate -------------------------------------------------------*/

#define BAUD 115200
#define BAUD_RATE ((SystemCoreClock)/((BAUD)*(16)))

/********************************** UART_configure() *****************************************************
 *
 * @name   -  UART_configure()
 * @brief  -  function to initialize UART
 * @param  -  none
 *
 * long description - This function configures UART control and status registers, sets baud rate, enables
 * 					  interrupts, selects clock mode and sets oversampling ratio.
 *
 * @return -  SUCCESS
 *
 ******************************************************************************************************/

/******************************** UART_configure() function declaration ***********************************/

CB_status UART_configure();

/********************************** UART_send() *****************************************************
 *
 * @name   -  UART_send()
 * @brief  -  function to send a character
 * @param  -  *data0 - pointer to data
 *
 * long description - This function sends a character by writing data to UART0 data register
 *
 * @return -  TX_SUCCESS
 *
 ******************************************************************************************************/

/******************************** UART_send() function declaration ***********************************/

CB_status UART_send(uint8_t *data0);

/********************************** UART_send_n() *****************************************************
 *
 * @name   -  UART_send_n()
 * @brief  -  function to send n characters
 * @param  -  *data0 : pointer to data
 * @param  -  length : length of data bytes
 *
 * long description - This function sends n characters by writing data to UART0 data register
 *
 * @return -  TX_SUCCESS
 *
 ******************************************************************************************************/

/******************************** UART_send_n() function declaration ***********************************/

CB_status UART_send_n(uint8_t *data0, uint8_t length);

/********************************** UART_receive() *****************************************************
 *
 * @name   -  UART_receive()
 * @brief  -  function to receive a character
 * @param  -  *data0 - pointer to data
 *
 * long description - This function receives a character by reading data from UART0 data register
 *
 * @return -  TX_SUCCESS
 *
 ******************************************************************************************************/

/******************************** UART_receive() function declaration ***********************************/

CB_status UART_receive(uint8_t *data0);

/********************************** UART_receive_n() *****************************************************
 *
 * @name   -  UART_receive_n()
 * @brief  -  function to receive n characters
 * @param  -  *data0 : pointer to data
 * @param  -  length : length of data bytes received
 *
 * long description - This function receives n characters by reading data from UART0 data register
 *
 * @return -  TX_SUCCESS
 *
 ******************************************************************************************************/

/******************************** UART_receive_n() function declaration ***********************************/

CB_status UART_receive_n(uint8_t *data0, uint8_t length);

/********************************** UART0_IRQHandler() *****************************************************
 *
 * @name   -  UART0_IRQHandler()
 * @brief  -  function to handle UART0 interrupts
 * @param  -  none
 *
 * long description - This function handles UART0 interrupts while receive and transmit operations.
 *
 * @return -  TX_IRQ : transmit interrupt
 * @return -  RX_IRQ : receive interrupt
 *
 ***********************************************************************************************************/

/******************************** UART0_IRQHandler() function declaration ***********************************/

CB_status UART0_IRQHandler();

#endif /* INCLUDES_UART_H_ */
