/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file profiler.c
 * @brief This file includes functions for profiling using Systick Timer.
 * @date November 29, 2017
 *
 * long description - The profiler.c file includes functions to -
 *                      1) configure the Systick profiler (profiler_start())
 *                      2) disable profiling (profiler_stop())
 *                      3) get systick val (gettime())
 *                      4) calculate execution time (execution_time())
 *                      5) handle Systick interupt (SysTick_Handler())
 *
 ***************************************************************************************************/

#ifndef SOURCES_PROFILER_H_
#define SOURCES_PROFILER_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include <stdlib.h>
#include "project3.h"

#define SYSTICK_MAX_VALUE 0x00FFFFFFU


uint32_t overflow;

/********************************** profiler_start() **********************************************************
 *
 * @name   -  profiler_start()
 * @brief  -  function to configure the Systick profiler.
 * @param  -  none
 *
 * long description - This function configures the Systick profiler.
 *
 * @return -  void
 *
 ********************************************************************************************************/

void profiler_start();

/********************************** profiler_stop() **********************************************************
 *
 * @name   -  profiler_stop()
 * @brief  -  function to disable profiling
 * @param  -  none
 *
 * long description - This function disables profiling.
 *
 * @return -  void
 *
 ********************************************************************************************************/

void profiler_stop();

/********************************** gettime() **********************************************************
 *
 * @name   -  gettime()
 * @brief  -  function to get systick val.
 * @param  -  none
 *
 * long description - This function gets systick val
 *
 * @return -  systick value
 *
 ********************************************************************************************************/

volatile uint32_t gettime();

/********************************** execution_time() **********************************************************
 *
 * @name   -  execution_time()
 * @brief  -  function to calculate execution time.
 * @param  -  start_time:systick val before code execution
 * @param  -  end_time:systick val after code execution
 *
 * long description - This function calculates execution time.
 *
 * @return -  execution time
 *
 ********************************************************************************************************/

volatile uint32_t execution_time(uint32_t start_time,uint32_t end_time);

/********************************** SysTick_Handler() **********************************************************
 *
 * @name   -  SysTick_Handler()
 * @brief  -  function to handle Systick interupt
 * @param  -  none
 *
 * long description - This function handles Systick interrupt.
 *
 * @return -  void
 *
 ********************************************************************************************************/

void SysTick_Handler(void);

#endif /* SOURCES_PROFILER_H_ */
