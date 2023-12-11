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

#include "profiler.h"
#include "project3.h"


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

/************************************ profiler_start() function definition ***********************************/
void profiler_start()
{
	SysTick->LOAD = SYSTICK_MAX_VALUE;
	SysTick->VAL = 5;
	SysTick->CTRL = 0x00000007;			//start timer
	overflow=0;
}

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

/************************************ profiler_stop() function definition ***********************************/

void profiler_stop()
{
	SysTick->CTRL = 0x00;				//stop timer
}


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

/************************************ gettime() function definition ***********************************/

volatile uint32_t gettime()
{
	return SysTick->VAL;
}


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

/************************************ execution_time() function definition ***********************************/

volatile uint32_t execution_time(uint32_t start_time,uint32_t end_time)
{
	uint32_t start = SYSTICK_MAX_VALUE - start_time;
	uint32_t end = (SYSTICK_MAX_VALUE - end_time)+(overflow*SYSTICK_MAX_VALUE);
	uint32_t clocks = end - start;
	uint8_t time1 = clocks/48;
	return time1;
}

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

 /************************************ SysTick_Handler() function definition ***********************************/

void SysTick_Handler(void)
{
	overflow++;
	if(TPM2_SC & TPM_SC_TOF_MASK)
	{
		TPM2->CNT = 10;							 // clear count
		TPM2_SC &= ~TPM_SC_TOF_MASK;			 // clear timer overflow flag
	}
}
