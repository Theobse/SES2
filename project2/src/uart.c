/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file uart.c
 * @brief This file includes UART functions
 * @date October 24, 2017
 *
 * long description - The uart.c file includes functions to -
 *                      1) configure UART (UART_Configure())
 *                      2) send a UART character (UART_send())
 *                      3) send n UART characters (UART_send_n())
 *                      4) receive UART character (UART_receive())
 *                      5) receive n UART characters (UART_receive_n())
 *                      6) handle UART interrupts (UART0_IRQHandler())
 *
 *
 ***************************************************************************************************/


/*----- Header-Files -------------------------------------------------------*/

#include "uart.h"
#include "circbuf.h"
#include "project2.h"

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

/******************************** UART_configure() function definition ***********************************/


CB_status UART_configure()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

	PORTA_PCR1 |= PORT_PCR_MUX(2);
	PORTA_PCR2 |= PORT_PCR_MUX(2);

	SIM->SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL(1);
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	uint16_t baud_rate = BAUD_RATE;
	UART0_BDL = (uint8_t)(baud_rate & UART0_BDL_SBR_MASK) ;
	UART0_BDH = (uint8_t)((baud_rate>>8) & UART0_BDH_SBR_MASK);

	UART0_C1 = 0x00;
	UART0_C3 = 0x00;
	UART0_S1 = 0x00;
	UART0_C4 = UART0_C4_OSR(15);

	UART0_C2 &= ~(UART0_C2_RE_MASK | UART0_C2_TE_MASK);
	UART0_C2 |=  (UART0_C2_RE_MASK | UART0_C2_TE_MASK);
	UART0_C2 |= UART0_C2_RIE_MASK;

	NVIC_EnableIRQ(UART0_IRQn);

	return SUCCESS;
}

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

/******************************** UART_send() function definition ***********************************/

CB_status UART_send(uint8_t *data0)
{
	UART0_D = *data0;
	return SUCCESS;
}

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

/******************************** UART_send_n() function definition ***********************************/


CB_status UART_send_n(uint8_t *data0, uint8_t length)
{
	uint8_t i = 0;

	for(i=0;i<length;i++)
	{
		//while(((UART0_S1)&(UART0_S1_TDRE_MASK)) != (UART0_S1_TDRE_MASK));
		UART0_D = *(data0 + i);
	}
	return SUCCESS;
}

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

/******************************** UART_receive() function definition ***********************************/


CB_status UART_receive(uint8_t *data0)
{
	*(data0) = UART0_D;
	return RX_SUCCESS;
}

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

/******************************** UART_receive_n() function definition ***********************************/

CB_status UART_receive_n(uint8_t *data0, uint8_t length)
{
	uint8_t i = 0;

		for(i=0;i<length;i++)
		{
			*(data0 + length) = UART0_D;
		}

	return RX_SUCCESS;
}

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

/******************************** UART0_IRQHandler() function definition ***********************************/

CB_status UART0_IRQHandler()
{

	if((UART0_S1 & UART0_S1_TDRE_MASK) && (!CB_is_empty(&Tx_Buffer))){
		CB_buffer_remove_item(&Tx_Buffer, &Tx_Data);
		UART_send(&Tx_Data);
		if(CB_is_empty(&Tx_Buffer)){
			UART0_C2 &= ~UART0_C2_TIE_MASK;
		}
		return TX_IRQ;
	}

	if((UART0_S1 & UART0_S1_RDRF_MASK ) && (!CB_is_full(&Rx_Buffer))){
		UART_receive(&Rx_Data);
		CB_buffer_add_item(&Rx_Buffer, &Rx_Data);
		if(CB_is_full(&Rx_Buffer)){
			UART0_C2 &= ~UART0_C2_RIE_MASK;
		}
		return RX_IRQ;
	}

	return NULL_ERROR;
}


