/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file project3_1.h
 * @brief This file includes logging functions for host and beaglebone black
 * @date November 23, 2017
 *
 * long description - The logger.c file includes functions to -
 *                      1) project3_1()
 *                      2) data()
 *                      3) profiling()
 *
 ***************************************************************************************************/


#ifndef SOURCES_PROJECT3_1_H_
#define SOURCES_PROJECT3_1_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "memory.h"

/********************************enum for LOG IDs****************************************************/

typedef enum{
	LOG_INITIALIZED = 100,
	GPIO_INITIALIZED,
	SYSTEM_INITIALIZED,
	SYSTEM_HALTED,
	INFO,
	WARNING,
	ERROR,
	PROFILING_STARTED,
	PROFILING_RESULT,
	PROFILING_COMPLETED,
	DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	DATA_NUMERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYSIS_COMPLETED,
	HEARTBEAT,
	DATA_INPUT_DISABLED,
	DATA_INPUT_ENABLED
}Log_Status;


/********************************** project3_1()**********************************************************
 *
 * @name   -  project3_1()
 * @brief  -  function to initialize log and other logging functions
 *
 * long description - This function executes logging for host and beaglebone black
 *
 * @return -  void
 *
 ******************************************************************************************************/
void project3_1();

/********************************** data()**********************************************************
 *
 * @name   -  data()
 * @brief  -  function to take data input and display data analysis
 *
 * long description - This function takes data input from user and performs data analysis
 *
 * @return -  void
 *
 ******************************************************************************************************/
void data();

/********************************** profiling()**********************************************************
 *
 * @name   -  data()
 * @brief  -  function to take data input and display data analysis
 *
 * long description - This function takes data input from user and performs data analysis
 *
 * @return -  void
 *
 ******************************************************************************************************/
void profiling();


/********************************** lib_memmove_test()**********************************************************
 *
 * @name   -  lib_memmove_test()
 * @brief  -  function to perform profiling on library memmove function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/
void lib_memmove_test(uint32_t len);

/********************************** lib_memset_test()**********************************************************
 *
 * @name   -  lib_memset_test()
 * @brief  -  function to perform profiling on library memset function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/
void lib_memset_test(uint32_t len);

/********************************** my_memmove_test()**********************************************************
 *
 * @name   -  my_memmove_test()
 * @brief  -  function to perform profiling on my_memmove function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/
void my_memmove_test(uint32_t len);

/********************************** my_memset_test()**********************************************************
 *
 * @name   -  my_memset_test()
 * @brief  -  function to perform profiling on my_memset function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/
void my_memset_test(uint32_t len);

#endif /* SOURCES_PROJECT3_1_H_ */
