/*
 * uart.c
 *
 *  Created on: 03-Dec-2017
 *      Author: defaultuser0
 */
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



uint8_t log_mode;
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

UART_status UART_configure()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 							/* Enable GPIOA Clock */
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;								/* Enable UART0 Clock */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

	PORTA_PCR1 |= PORT_PCR_MUX(2); 									/* Configuring PCR1 to alt2 for UART0 */
	PORTA_PCR2 |= PORT_PCR_MUX(2);



	/* Configuring PCR2 to alt2 for UART0 */

	SIM->SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL(1); 							/* Selecting PLL clock mode */
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);  							/* Using MCGFLLPLL */

	uint16_t baud_rate = BAUD_RATE; 								/* Setting baud rate registers */
	UART0_BDL = (uint8_t)(baud_rate & UART0_BDL_SBR_MASK) ;
	UART0_BDH = (uint8_t)((baud_rate>>8) & UART0_BDH_SBR_MASK);

	UART0_C1 = 0x00;												/* Configuring C1 control register */
	UART0_C3 = 0x00; 												/* Configuring C3 control register */
	UART0_S1 = 0x00; 												/* Configuring S1 status register */
	UART0_C4 = UART0_C4_OSR(15); 									/* Setting OSR bit field to 16 */

	UART0_C2 &= ~(UART0_C2_RE_MASK | UART0_C2_TE_MASK); 			/* Clear TE and RE */
	UART0_C2 |=  (UART0_C2_RE_MASK | UART0_C2_TE_MASK); 			/* Set TE and RE */
	UART0_C2 |= UART0_C2_RIE_MASK; 									/* Set RIE */
	//UART0_C2 &= ~UART0_C2_TIE_MASK;
	//UART0_C2 |= UART0_C2_TIE_MASK;

	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//if(log_mode == 0x43){
	NVIC_SetPriority(UART0_IRQn,12);
	//NVIC_CLearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
	//}									/* Enable UART0 Interrupt */

	return UART_CONFIG_SUCCESS;
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

UART_status UART_send(uint8_t *data0)
{
		while(!(UART0_S1 & UART0_S1_TDRE_MASK));
		UART0_D = *data0;
												/* Writing data to UART0 data register */
	return TX_SUCCESS;
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

UART_status UART_send_n(uint8_t *data0, uint8_t length)
{
	uint8_t i = 0;
	if(log_mode == 0x43){
		for(i=0;i<length;i++){
			UART0_D = *(data0 + i);										/* Writing data to UART0 data register */
		}
	}
	else{
	for(i=0;i<length;i++)
	{
		while(!(UART0_S1 & UART0_S1_TDRE_MASK));
		UART0_D = *(data0 + i);										/* Writing data to UART0 data register */
	}
	}
	return TX_SUCCESS;
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

UART_status UART_receive(uint8_t *data0)
{
	if(log_mode == 0x43){
		*(data0) = UART0_D;
	}
	else{
		while(!(UART0_S1 & UART0_S1_RDRF_MASK));
		*(data0) = UART0_D;												/* Reading data from UART0 data register */
	}
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

UART_status UART_receive_n(uint8_t *data0, uint8_t length)
{
	uint8_t i = 0;
	if(log_mode == 0x43){
		for(i=0;i<length;i++){
			*(data0 + i) = UART0_D;							/* Reading data from UART0 data register */
		}
	}
	else{
		for(i=0;i<length;i++){
			while(!(UART0_S1 & UART0_S1_RDRF_MASK));
			*(data0 + i) = UART0_D;							/* Reading data from UART0 data register */
		}
	}													/* Reading data from UART0 data register */
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

UART_status UART0_IRQHandler(void)
{
	//if((UART0_S1 & UART0_S1_TDRE_MASK) && (!CB_is_empty(&Tx_Buffer))){ /* Check if TDRE set and Transmit buffer is not empty */
	//	CB_buffer_remove_item(&Tx_Buffer, &Tx_Data);				   /* Write data from Tx_Buffer to Tx_data */
	//	UART_send(&Tx_Data);										   /* Send data from Tx_Data */
	//	if(CB_is_empty(&Tx_Buffer)){								   /* Check if Transmit buffer is empty */
	//		UART0_C2 &= ~UART0_C2_TIE_MASK;							   /* Clear TIE bit */
	//	}
	//	return TX_IRQ;
	//}

	//__disable_irq();


	if((UART0_S1 & UART0_S1_RDRF_MASK ) && (!CB_is_full(&Rx_Buffer))){ /* Check if RDRF set and Receive buffer is not full */
		START_CRITICAL();
		UART_receive(&Rx_Data);										   /* Write received data to Rx_Data */
		CB_buffer_add_item(&Rx_Buffer, &Rx_Data);					   /* Add data from Rx_Data to Rx_Buffer */
		if(CB_is_full(&Rx_Buffer)){									   /* Check if Receive buffer is full */
			UART0_C2 &= ~UART0_C2_RIE_MASK;							   /* Clear RIE bit */
		}
		END_CRITICAL();
		return RX_IRQ;
	}

	if((UART0_S1 & UART0_S1_TDRE_MASK) && (!(Log_buffer_is_empty(&log_buffer)))){ /* Check if TDRE set and Transmit buffer is not empty */
		START_CRITICAL();
			Log_buffer_remove_item(&log_buffer, &Log_Tx_Data);
			//log_mode = 0x43;/* Write data from Tx_Buffer to Tx_data */
			UART_send(&Log_Tx_Data);										   /* Send data from Tx_Data */
			if(Log_buffer_is_empty(&log_buffer) == LOG_BUFFER_EMPTY){								   /* Check if Transmit buffer is empty */
				UART0_C2 &= ~UART0_C2_TIE_MASK;							   /* Clear TIE bit */
			}
		END_CRITICAL();
		return TX_IRQ;
	}
	else{
		return UART_CONFIG_SUCCESS;

	}
	//__enable_irq();
}


