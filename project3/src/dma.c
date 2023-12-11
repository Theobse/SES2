/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file dma.c
 * @brief This source file includes UART function definitions
 * @date December 03, 2017
 *
 * long description - The dma.c file includes functions to -
 *                      1) move data from source address to destination address using DMA (memmove_dma())
 *                      2) set a length of data bytes to a particular value using DMA (memset_dma())
 *                      3) handle DMA interrupts (DMA0_IRQHandler())
 *
 *
 ***************************************************************************************************/

#include "dma.h"

/********************************** memmove_dma() ********************************************
 *
 * @name  memmove_dma
 * @brief function to move length of bytes data from source to destination using DMA
 * @param 1) *src - pointer to a source memory location.
 *        2) *dst - pointer to a destination memory location
 *        3) length - length of data bytes to be moved.
 *        4) size - byte-transfer size
 *
 * long description - This function takes two byte pointers (one source and one destination)
 *                    and a length of bytes to copy from the source location (src) to the
 *                    destination(dst) using DMA.
 *
 *************************************************************************************************/


 /**************************** memmove_dma() function definition **********************************/

void memmove_dma(void *src, void *dst, uint32_t length, uint8_t size)
{
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;		//enable clock for DMA
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;		//enable clock for DMAMUX

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA MUX channel
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	//clear DMA0 status bits and DMA0 interrupt bit

	DMA_SAR0 = (uint32_t)src;				//copy source address
	DMA_DAR0 = (uint32_t)dst;				//copy destination address

	DMA_DSR_BCR0 |= length;  				// number of bytes to transfer
	DMA_DCR0 |= DMA_DCR_SINC_MASK;			// increment SAR
	DMA_DCR0 |= DMA_DCR_DINC_MASK;			// increment DAR

	if(size==EIGHT_BIT)
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;				// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	else if(size==SIXTEEN_BIT)
		{
			DMA_DCR0 |= SIXTEEN_BIT_SOURCE_MASK;		// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= SIXTEEN_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else if(size==THIRTYTWO_BIT)
		{
			DMA_DCR0 |= THIRTYTWO_BIT_SOURCE_MASK;		// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= THIRTYTWO_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;				// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	DMA_DCR0 |= DMA_DCR_AA_MASK;						//enable auto align

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;			//enable DMA MUX channel

	DMA_DCR0 |= DMA_DCR_EINT_MASK;						//enable DMA interrupt

	NVIC_SetPriority(DMA0_IRQn,0);
	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq;

	DMA_DCR0 |= DMA_DCR_START_MASK;						//start DMA transfer
}

/********************************** memset_dma() *************************************************
 *
 * @name  memset_dma
 * @brief function to set a length of data bytes to a specified value using DMA
 * @param 1) *src - pointer to a source memory location.
 *        2) length - length of data bytes to be set to the specified value.
 *        3) value - value to be set for each byte
 *        4) size - byte-transfer size
 *
 * long description - This function takes a pointer to a source memory location(src) and
 *                    a consecutive length in bytes are set to the specified value using DMA.
 *
 *************************************************************************************************/

 /**************************** memset_dma() function definition **********************************/

void memset_dma(uint8_t value, void *dst, uint32_t length, uint8_t size)
{
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;		//enable clock for DMA
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;		//enable clock for DMAMUX

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA MUX channel
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	//clear DMA0 status bits and DMA0 interrupt bit

	DMA_SAR0 = (uint32_t)&value;			//copy source address
	DMA_DAR0 = (uint32_t)dst;				//copy destination address

	DMA_DSR_BCR0 |= length;  				// number of bytes to transfer
	DMA_DCR0 |= DMA_DCR_SINC_MASK;			// increment SAR
	DMA_DCR0 |= DMA_DCR_DINC_MASK;			// increment DAR

	if(size==EIGHT_BIT)
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;			// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	else if(size==SIXTEEN_BIT)
		{
			DMA_DCR0 |= SIXTEEN_BIT_SOURCE_MASK;	// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= SIXTEEN_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else if(size==THIRTYTWO_BIT)
		{
			DMA_DCR0 |= THIRTYTWO_BIT_SOURCE_MASK;	// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= THIRTYTWO_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;			// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;	//enable DMA MUX channel

	DMA_DCR0 |= DMA_DCR_EINT_MASK;			//enable DMA interrupt

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq;

	DMA_DCR0 |= DMA_DCR_START_MASK;			//start DMA transfer

	//while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));		//check if transfer is completed
}

/********************************** DMA0_IRQHandler() ********************************************************
 *
 * @name   -  DMA0_IRQHandler()
 * @brief  -  function to handle DMA interrupt
 * @param  -  none
 *
 * long description - This function handles DMA interrupt.
 *
 * @return -  void
 *
 *************************************************************************************************************/

/********************************* DMA0_IRQHandler() function definition ************************************/

void DMA0_IRQHandler()
{
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;		//clear DMA0 status bits and DMA0 interrupt bit
}
