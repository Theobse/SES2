/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file dma.h
 * @brief This header file includes UART function declarations.
 * @date December 03, 2017
 *
 * long description - The dma.c file includes functions declarations of functions to -
 *                      1) move data from source address to destination address using DMA (memmove_dma())
 *                      2) set a length of data bytes to a particular value using DMA (memset_dma())
 *                      3) handle DMA interrupts (DMA0_IRQHandler())
 *
 *
 ***************************************************************************************************/

#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_

#include "MKL25Z4.h"
#include <stdlib.h>
#include <stdint.h>
#include "project3.h"

#define EIGHT_BIT		8
#define SIXTEEN_BIT		16
#define THIRTYTWO_BIT	32

#define EIGHT_BIT_SOURCE_MASK		(DMA_DCR_SSIZE(1))
#define SIXTEEN_BIT_SOURCE_MASK		(DMA_DCR_SSIZE(2))
#define THIRTYTWO_BIT_SOURCE_MASK	(DMA_DCR_SSIZE(0))

#define EIGHT_BIT_DESTINATION_MASK		(DMA_DCR_DSIZE(1))
#define SIXTEEN_BIT_DESTINATION_MASK	(DMA_DCR_DSIZE(2))
#define THIRTYTWO_BIT_DESTINATION_MASK	(DMA_DCR_DSIZE(0))

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

 /**************************** memmove_dma() function declaration **********************************/


void memmove_dma(void *src, void *dst, uint32_t length, uint8_t size);


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

 /**************************** memset_dma() function declaration **********************************/

void memset_dma(uint8_t value, void *dst, uint32_t length, uint8_t size);


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

/********************************* DMA0_IRQHandler() function declaration ************************************/

void DMA0_IRQHandler();

#endif /* SOURCES_DMA_H_ */
