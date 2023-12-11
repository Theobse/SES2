/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file main.c
 * @brief This file includes logging functions
 * @date December 3, 2017
 *
 * long description-1) main file of project 3 to perform logger, 
 *				profiling spi_nrf testing for kl25z
 *                  2) logger for BBB and Host    
 *
 ***************************************************************************************************/

#ifdef PROJECT3
#include "project3.h"
#endif

#ifdef PROJECT3_1
#include "project3_1.h"
#endif

int main(void)
{
	#ifdef PROJECT3
	project3();
	#endif
	#ifdef PROJECT3_1
	project3_1();
	#endif
}
