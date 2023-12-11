/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file project3.h
 * @brief This file includes logging functions
 * @date December 3, 2017
 *
 * long description - The logger.c file includes functions to -
 *                      1) project3() to initialise logging functions
 *                      2) data() to log data receive and data analysis
 *                      3) profiling() to perform profiling function on library, NON-DMA and DMA
 *                         memmove and memmset functions
 *
 ***************************************************************************************************/

#ifndef SOURCES_PROJECT3_H_
#define SOURCES_PROJECT3_H_

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
#include "test.h"

#define START_CRITICAL()	__disable_irq()
#define END_CRITICAL()		__enable_irq()

#define NON_BLOCKING_MODE			(0x43)
#define BLOCKING_MODE				(0x44)

/*------------------------extern variables---------------------------*/
extern uint8_t Tx_Data;
extern uint8_t Rx_Data;
extern uint8_t Rxd_Data;
extern uint8_t character_count[4];
extern uint8_t char_str[4][10];
extern uint8_t *num;
extern uint8_t *alpha;
extern uint8_t *punc;
extern uint8_t *misc;
extern uint8_t time[4];
extern uint8_t t;

/*********************************** project3() **********************************************************
 *
 * @name   -  project3()
 * @brief  -  function to pass logs to log buffer and then print it to terminal through terminal
 *
 * long description - This function takes data input from user and depending on the received data
 * 						it performs various logging functions such as data analysis and profiling
 *
 * @return -  void
 *
 ******************************************************************************************************/

void project3();

/************************************ data() **********************************************************
 *
 * @name   -  data()
 * @brief  -  function to perform data analysis on the data received through uart
 *
 * @return -  void
 *
 ******************************************************************************************************/

void data();

/************************************ profiling() **********************************************************
 *
 * @name   -  profiling()
 * @brief  -  function to perform profiling operation on library, NON-DMA and DMA memmove and memset functions
 *
 * @return -  void
 *
 ******************************************************************************************************/

void profiling();

#endif /* SOURCES_PROJECT3_H_ */
