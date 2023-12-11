/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file spi.c
 * @brief This file includes Circular Buffer functions
 * @date November 26, 2017
 *
 * long description - The spi.c file includes functions to -
 *                      1) SPI initialization function SPI_init()
 *                      2) SPI status function SPI_status()
 *                      3) SPI write function SPI_write() to write one byte data
 *                      4) SPI read function SPI_write() to read one byte data
 *                      5) SPI send packet function SPI_send_packet() to write n bytes of data
 *                      6) SPI_flush() function to disable SPI
 *
 ***************************************************************************************************/


/*----- Header-Files -------------------------------------------------------*/

#include "spi.h"
#include "gpio.h"

/********************************** SPI_init() *****************************************************
 *
 * @name   -  SPI_init()
 * @brief  -  function to initialize SPI
 *
 * long description - This function initializes SPI i.e sets baud rate and enables SPI transfer
 *
 ***************************************************************************************************/

void SPI_init(void)
{

	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;  				//enable clock for SPI_0


	SPI0->BR = (SPI_BR_SPPR(0x01) | SPI_BR_SPR(0x00));	//baud rate

	SPI0->C1 = 0x50;
}


/********************************** SPI_status() ***************************************************
 *
 * @name   -  SPI_status()
 * @brief  -  function to read status of SPI
 *
 * long description - This function reads SPI status register and returns the value
 *
 * @return -  SPI0->S : value of SPI status register
 *
 ***************************************************************************************************/

uint8_t SPI_status()
{
	return SPI0->S; 									//return SPI status
}

/********************************** SPI_write_byte(uint8_t byte) ***********************************
 *
 * @name   -  SPI_write_byte(uint8_t byte)
 * @brief  -  function to write one byte of data
 *
 * long description - This function takes in the byte to be written and transfers it through SPI
 *
 ***************************************************************************************************/


void SPI_write_byte(uint8_t byte)
{
	while (!(SPI0->S & 0x20)); 							//check whether transfer buffer is empty
	SPI0->D = byte;										//write data
}

/********************************** SPI_read_byte() ***************************************************
 *
 * @name   -  SPI_read_byte()
 * @brief  -  function reads byte in SPI data register after receiving is completed
 *
 * long description - This function reads SPI data register and returns the value
 *
 * @return -  byte : value of SPI data register
 *
 ***************************************************************************************************/

uint8_t SPI_read_byte()
{
	uint8_t byte;
	while (!(SPI0->S & 0x80)); 							//check whether receive buffer is full
	byte = SPI0->D; 									//read data
	return byte; 										//return data
}

/****************************SPI_send_packet(uint8_t *p, uint8_t length) ***************************
 *
 * @name   -  SPI_send_packet(uint8_t *p, uint8_t length)
 * @brief  -  function to write n bytes of data to SPI
 *
 * long description - This function takes in the length and pointer to the data to be written and
 * 	                  transfers it through SPI
 *
 ***************************************************************************************************/

void SPI_send_packet(uint8_t *p, uint8_t length)
{
	uint8_t i = 0;
	for(i=0;i<length;i++)
	{
		while (!(SPI0->S & 0x20));  					//check whether transfer buffer is empty
		SPI0->D = *(p+i); 								//write data
	}
}

/********************************** SPI_flush() *****************************************************
 *
 * @name   -  SPI_flush()
 * @brief  -  function to disable SPI and reinitialize it
 *
 * long description - This function disable SPI module and reinitializes SPI
 *
 ****************************************************************************************************/

void SPI_flush()
{
	SPI0->C1= SPI0->C1 & 0xBF; 							//SPI module disable
	SPI_init();											//reinitialize SPI
}

/********************************** delay() *****************************************************
 *
 * @name   -  delay()
 * @brief  -  function to set delay
 *
 * long description - This function is used to set a delay
 *
 ****************************************************************************************************/

void delay()
{
	uint32_t i=0;
	for(i=0;i<1000;i++);
}

