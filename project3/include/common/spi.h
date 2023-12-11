/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file spi.h
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

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

/*----- Header-Files -------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "MKL25Z4.h"
#include "gpio.h"

/********************************** SPI_init() *****************************************************
 *
 * @name   -  SPI_init()
 * @brief  -  function to initialize SPI
 *
 * long description - This function initializes SPI i.e sets baud rate and enables SPI transfer
 *
 ***************************************************************************************************/

void SPI_init();

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

uint8_t SPI_status();

/********************************** SPI_write_byte(uint8_t byte) ***********************************
 *
 * @name   -  SPI_write_byte(uint8_t byte)
 * @brief  -  function to write one byte of data
 *
 * long description - This function takes in the byte to be written and transfers it through SPI
 *
 ***************************************************************************************************/

void SPI_write_byte(uint8_t byte);

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

uint8_t SPI_read_byte();

/****************************SPI_send_packet(uint8_t *p, uint8_t length) ***************************
 *
 * @name   -  SPI_send_packet(uint8_t *p, uint8_t length)
 * @brief  -  function to write n bytes of data to SPI
 *
 * long description - This function takes in the length and pointer to the data to be written and
 * 	                  transfers it through SPI
 *
 ***************************************************************************************************/

void SPI_send_packet(uint8_t *p, uint8_t length);

/********************************** SPI_flush() *****************************************************
 *
 * @name   -  SPI_flush()
 * @brief  -  function to disable SPI and reinitialize it
 *
 * long description - This function disable SPI module and reinitializes SPI
 *
 ****************************************************************************************************/


void SPI_flush();

/********************************** delay() *****************************************************
 *
 * @name   -  delay()
 * @brief  -  function to set delay
 *
 * long description - This function is used to set a delay
 *
 ****************************************************************************************************/

void delay();

#endif /* SOURCES_SPI_H_ */
