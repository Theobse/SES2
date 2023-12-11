/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file test.h
 * @brief This file includes function declarations of functions for testing profiling, spi and nrf
 * @date December 06, 2017
 *
 * long description - The test.c file includes function declarations of functions to -
 *                      1) test profile time for memory functions dma,non-dma,stdlib) (profile_test())
 *                      2) test read and write operation to nrf module (spi_nrf_test())
 *                      3) test config read and write operation to nrf module (config_reg_test())
 *                      4) test read and write operation to nrf module (tx_addr_test())
 *                      5) test read and write operation to nrf module (rf_setup_test())
 *                      6) test read and write operation to nrf module (rf_ch_reg_test())
 *                      7) read the status register of nrf module (status_reg_test())
 *                      8) read the status register of nrf module (fifo_status_reg_test())
 *                      9) test and log on UART the success of read and write operations for nrf registers (transmit())
 *                     10) test profiling time of memmove (stdlib) function (lib_memmove_test())
 *                     11) test profiling time of memmove (non-dma) function (my_memmove_test())
 *                     12) test profiling time of memmove (dma) function (dma_memmove_test())
 *                     13) test profiling time of memset (dma) function (dma_memset_test())
 *                     14) test profiling time of memset (non-dma) function (my_memset_test())
 *                     15) test profiling time of memset (stdlib) function (lib_memset_test())
 *
 ***************************************************************************************************/

#ifndef SOURCES_TEST_H_
#define SOURCES_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "rtc.h"
#include "logger.h"
#include "logbuf.h"
#include "uart.h"
#include "circbuf.h"
#include "gpio.h"
#include "dma.h"
#include "profiler.h"
#include "project3.h"
#include "spi.h"
#include "nordic.h"
#include "memory.h"

enum{
CONFIG=0,
TXADDR=1,
RFSETUP=2,
RFCH=3,
STATUS=4,
FIFO=5
};

/*----- Macros for character strings -------------------------------------------------------*/

#define CON_REG			"Config register write	:"
#define TXADDR_REG 		"TXADDR register write	:"
#define RFSETUP_REG 	"RFSETUP register write	:"
#define RFCH_REG 		"RFCH register write	:"
#define STAT_REG 		"STATUS register read	:"
#define FIFO_REG		"FIFO register read	:"


/********************************** profile_test()**********************************************************
 *
 * @name   -  profile_test()
 * @brief  -  function to test profile time for memory functions dma,non-dma,stdlib)
 * @param  -  none
 *
 * long description - This function passes log struct to log buffer.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void profile_test();

/********************************** spi_nrf_test()()**********************************************************
 *
 * @name   -  spi_nrf_test()
 * @brief  -  function to test read and write operation to nrf module
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/
void spi_nrf_test();

/********************************** dma_memmove_test()**********************************************************
 *
 * @name   -  dma_memmove_test()
 * @brief  -  function to test profiling time of memmove (dma) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memmove (dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void dma_memmove_test(uint32_t len);

/********************************** dma_memset_test()**********************************************************
 *
 * @name   -  dma_memset_test()
 * @brief  -  function to test profiling time of memset (dma) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memset (dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void dma_memset_test(uint32_t len);

/********************************** my_memmove_test()**********************************************************
 *
 * @name   -  my_memmove_test()
 * @brief  -  function to test profiling time of memmove (non-dma) function
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memmove (non-dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void my_memmove_test(uint32_t len);

/********************************** my_memset_test()**********************************************************
 *
 * @name   -  my_memset_test()
 * @brief  -  function to test profiling time of memset (non-dma) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memset (non-dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void my_memset_test(uint32_t len);

void my_memmove_test_optimized(uint32_t len);

void my_memset_test_optimized(uint32_t len);


/********************************** lib_memmove_test()**********************************************************
 *
 * @name   -  lib_memmove_test()
 * @brief  -  function to test profiling time of memmove (stdlib) function
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memmove (stdlib) function
 *
 * @return -  void
 *
 ******************************************************************************************************/
void lib_memmove_test(uint32_t len);

/********************************** lib_memset_test()**********************************************************
 *
 * @name   -  lib_memset_test()
 * @brief  -  function to test profiling time of memset (stdlib) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memset (stdlib) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void lib_memset_test(uint32_t len);

/********************************** config_reg_test()**********************************************************
 *
 * @name   -  config_reg_test()
 * @brief  -  function to test config read and write operation to nrf module.
 * @param  -  none
 * long description - This function tests config read and write operation to nrf module.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void config_reg_test();

/********************************** tx_addr_test()**********************************************************
 *
 * @name   -  tx_addr_test()
 * @brief  -  function to test read and write operation to nrf module.
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/
void tx_addr_test();

/********************************** rf_setup_test()**********************************************************
 *
 * @name   -  rf_setup_test()
 * @brief  -  function to test read and write operation to nrf module.
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module.
 *
 * @return -  void
 *
 ******************************************************************************************************/
void rf_setup_test();

/********************************** rf_ch_reg_test()**********************************************************
 *
 * @name   -  rf_ch_reg_test()
 * @brief  -  function to test read and write operation to nrf module
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/
void rf_ch_reg_test();

/********************************** status_reg_test() **********************************************************
 *
 * @name   -  status_reg_test()
 * @brief  -  function to read the status register of nrf module
 * @param  -  none
 *
 * long description - This function reads the status register of nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/
void status_reg_test();

/********************************** fifo_status_reg_test() **********************************************************
 *
 * @name   -  fifo_status_reg_test()
 * @brief  -  function to read the fifo status register of nrf module
 * @param  -  none
 *
 * long description - This function reads the fifo status register of nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/
void fifo_status_reg_test();

/********************************** transmit()**********************************************************
 *
 * @name   -  transmit()
 * @brief  -  function to test and log on UART the success of read and write operations for nrf registers
 * @param  -  result: result value obtained after operations.
 *
 * long description - This function tests and logs on UART the success of read and write operations for nrf registers
 *
 * @return -  void
 *
 ******************************************************************************************************/

void transmit(uint8_t result);

#endif /* SOURCES_TEST_H_ */
