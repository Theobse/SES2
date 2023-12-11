/***************************************************************************************************
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file nordic.c
 * @brief This file includes functions to communicate and configure nrf module.
 * @date December 03, 2017
 *
 * long description - The nordic.c file includes functions to -
 *                      1) nrf_read_register()
 *                      2) nrf_write_register()
 *                      3) nrf_read_status()
 *                      4) nrf_read_config()
 *                      5) nrf_write_config()
 *                      6) nrf_read_rf_setup()
 *                      7) nrf_write_rf_setup()
 *                      8) nrf_read_rf_ch()
 *                      9) nrf_read_TX_ADDR()
 *                     10) nrf_write_TX_ADDR()
 *                     11) nrf_read_fifo_status()
 *                     12) nrf_flush_rx_fifo()
 *                     13) nrf_flush_tx_fifo()
 *
 ***************************************************************************************************/

#ifndef SOURCES_NORDIC_H_
#define SOURCES_NORDIC_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include "MKL25Z4.h"
#include "spi.h"
#include "gpio.h"

#define nrf_chip_enable()  			(PTD_BASE_PTR->PCOR = 1)
#define nrf_chip_disable() 			(PTD_BASE_PTR->PSOR = 1)
#define nrf_transmit_enable()		(PTD_BASE_PTR->PCOR = 1<<5)
#define nrf_transmit_disable()		(PTD_BASE_PTR->PSOR = 1<<5)

#define CONFIG_REG 			(0x00)
#define EN_AA_REG 			(0x01)
#define EN_RXADDR_REG 		(0x02)
#define SETUP_AW_REG 		(0x03)
#define SETUP_RETR_REG 		(0x04)
#define RF_CH_REG 			(0x05)
#define RF_SETUP_REG 		(0x06)
#define STATUS_REG 			(0x07)
#define RX_ADDR_P0_REG 		(0x0A)
#define RX_ADDR_P1_REG 		(0x0B)
#define TX_ADDR 			(0x10)
#define FIFO_STATUS_REG 	(0x17)

#define R_REGISTER     		(0x00)
#define W_REGISTER		    (0x20)
#define W_TX_PAYLOAD 		(0xA0)
#define R_RX_PAYLOAD 		(0x61)
#define FLUSH_TX		    (0xE1)
#define FLUSH_RX		    (0xE2)

// STATUS Register Bits
#define STATUS_RX_DR(x)    	 (uint8_t)((uint8_t)(x)<<6)
#define STATUS_TX_DS(x)      (uint8_t)((uint8_t)(x)<<5)
#define STATUS_MAX_RT(x)     (uint8_t)((uint8_t)(x)<<4)
#define STATUS_RX_P_NO_0   	 (0x00)
#define STATUS_RX_P_NO_1   	 (0x02)
#define STATUS_RX_P_NO_2   	 (0x04)
#define STATUS_RX_P_NO_3   	 (0x06)
#define STATUS_RX_P_NO_4   	 (0x08)
#define STATUS_RX_P_NO_5   	 (0x0A)

// CONFIG Register Bits
#define CONFIG_MASK_RX_DR(x)  (uint8_t)((uint8_t)(x)<<6)
#define CONFIG_MASK_TX_DS(x)  (uint8_t)((uint8_t)(x)<<5)
#define CONFIG_MASK_MAX_RT(x) (uint8_t)((uint8_t)(x)<<4)
#define CONFIG_EN_CRC(x)      (uint8_t)((uint8_t)(x)<<3)
#define CONFIG_CRCO_1      	  (0x00)
#define CONFIG_CRCO_2 	  	  (0x04)
#define CONFIG_POWER_UP    	  (0x02)
#define CONFIG_POWER_DOWN  	  (0x00)
#define CONFIG_PRIM_RX     	  (0x01)
#define CONFIG_PRIM_TX     	  (0x00)

// RF_SETUP Register Bits
#define RF_SETUP_PLL_LOCK(x)  (uint8_t)((uint8_t)(x)<<4)
#define RF_SETUP_RF_DR(x)  	  (uint8_t)((uint8_t)(x)<<3)
#define RF_SETUP_LNA_HCURR(x) (uint8_t)((uint8_t)(x))

// RF_CH Register Bits
#define RF_CH(x)			  (uint8_t)(x);

// FIFO_STATUS Register Bits
#define FIFO_STATUS_TX_REUSE  (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<6))
#define FIFO_STATUS_TX_FULL   (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<5))
#define FIFO_STATUS_TX_EMPTY  (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<4))
#define FIFO_STATUS_RX_FULL   (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<1))
#define FIFO_STATUS_RX_EMPTY  (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<0))

/********************************** nrf_read_register() **********************************************************
 *
 * @name   -  nrf_read_register()
 * @brief  -  function to read a value from a register of nordic module
 * @param  -  register whose value is to be read
 *
 * long description - This function reads the value from the register and returns the value
 *
 * @return -  a(register value)
 *
 ********************************************************************************************************/

/************************************ nrf_read_register() function definition ***********************************/

uint8_t nrf_read_register(uint8_t reg);

 /********************************** nrf_write_register() **********************************************************
  *
  * @name   -  nrf_write_register()
  * @brief  -  function to write a value to a register of nordic module
  * @param  -  address of the register and the value  to be written in the register
  *
  * long description - This function writes a value to the specified register
  *
  * @return -  void
  *
  ********************************************************************************************************/

 /************************************ nrf_write_register() function definition ***********************************/

void nrf_write_register(uint8_t reg, uint8_t value);

/********************************** nrf_read_status() **********************************************************
 *
 * @name   -  nrf_read_status()
 * @brief  -  function to read a value of status
 *
 * long description - This function reads the value from status register
 *
 * @return -  a(register value)
 *
 ********************************************************************************************************/

/************************************ nrf_read_status() function definition ***********************************/

uint8_t nrf_read_status();

/********************************** nrf_read_config() **********************************************************
 *
 * @name   -  nrf_read_config()
 * @brief  -  function to read a value of status
 *
 * long description - This function reads the value from config register
 *
 * @return -  a(register value)
 *
 ********************************************************************************************************/

/************************************ nrf_read_config() function definition ***********************************/

uint8_t nrf_read_config();

/********************************** nrf_write_config() **********************************************************
 *
 * @name   -  nrf_write_config()
 * @brief  -  function to write a value to config register
 *
 * long description - This function writes a value to config register
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ nrf_read_config() function definition ***********************************/

void nrf_write_config(uint8_t config);

/********************************** nrf_read_rf_setup() **********************************************************
 *
 * @name   -  nrf_read_rf_setup()
 * @brief  -  function to read a value of rf setup
 *
 * long description - This function reads the value from rf setup register
 *
 * @return -  a(register value)
 *
 ********************************************************************************************************/

/************************************ nrf_read_rf_setup() function definition ***********************************/

uint8_t nrf_read_rf_setup();

/********************************** nrf_write_rf_setup() **********************************************************
 *
 * @name   -  nrf_write_rf_setup()
 * @brief  -  function to write a value to rf setup register
 *
 * long description - This function writes a value to rf setup register
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ nrf_read_rf_setup() function definition ***********************************/

void nrf_write_rf_setup(uint8_t config);

/********************************** nrf_read_rf_ch() **********************************************************
 *
 * @name   -  nrf_read_rf_ch()
 * @brief  -  function to read a value of rf channel register
 *
 * long description - This function reads the value from rf channel register
 *
 * @return -  a(register value)
 *
 ********************************************************************************************************/

/************************************ nrf_read_rf_ch() function definition ***********************************/

uint8_t nrf_read_rf_ch();

/********************************** nrf_write_rf_ch() **********************************************************
 *
 * @name   -  nrf_write_rf_channel()
 * @brief  -  function to write a value to rf chennel register
 *
 * long description - This function writes a value to rf channel register
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ nrf_read_rf_ch() function definition ***********************************/

void nrf_write_rf_ch(uint8_t channel);

/********************************** nrf_read_TX_ADDR() **********************************************************
 *
 * @name   -  nrf_read_TX_ADDR()
 * @brief  -  function to read a value of TX ADDR register
 *
 * long description - This function reads the value from TX ADDR register
 *
 * @return -  a(register value)
 *
 ********************************************************************************************************/

/************************************ nrf_read_TX_ADDR() function definition ***********************************/

void nrf_read_TX_ADDR(uint8_t *address);

/********************************** nrf_write_TX_ADDR() **********************************************************
 *
 * @name   -  nrf_write_TX_ADDR()
 * @brief  -  function to write a value to TX ADDR register
 *
 * long description - This function writes a value to TX ADDR register
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ nrf_read_TX_ADDR() function definition ***********************************/

void nrf_write_TX_ADDR(uint8_t *tx_addr);

/********************************** nrf_read_fifo_status() **********************************************************
 *
 * @name   -  nrf_read_fifo_status()
 * @brief  -  function to read a value of fifo status register
 *
 * long description - This function reads the value from fifo status register
 *
 * @return -  a(register value)
 *
 ********************************************************************************************************/

/************************************ nrf_read_fifo_status() function definition ***********************************/

uint8_t nrf_read_fifo_status();

/********************************** nrf_flush_rx_fifo() **********************************************************
 *
 * @name   -  nrf_flush_rx_fifo()
 * @brief  -  function to write flush_rx command
 *
 * long description - This function writes a flush_rx command
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ nrf_flush_rx_fifo() function definition ***********************************/

void nrf_flush_tx_fifo();

/********************************** nrf_flush_tx_fifo() **********************************************************
 *
 * @name   -  nrf_flush_tx_fifo()
 * @brief  -  function to write flush_tx command
 *
 * long description - This function writes a flush_tx command
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ nrf_flush_tx_fifo() function definition ***********************************/

void nrf_flush_rx_fifo();

#endif /* SOURCES_NORDIC_H_ */
