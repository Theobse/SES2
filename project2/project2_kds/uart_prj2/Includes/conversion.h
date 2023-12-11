/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file conversion.c
 * @brief This file integer to ascii conversion function
 * @date October 2, 2017
 *
 * long description - The conversion.c file includes function to -
 *                1) convert a signed 32-bit integer to ascii character string of any base(my_itoa())
 *
 ***************************************************************************************************/

#ifndef INCLUDES_CONVERSION_H_
#define INCLUDES_CONVERSION_H_

/*----- Header-Files -------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <math.h>

/********************************** my_itoa() *****************************************************
 *
 * @name   -  my_itoa()
 * @brief  -  function for integer to ascii conversion function
 * @param  -  data : signed 32-bit integer to be converted to ascii string of specified base
 * @param  -  *ptr : pointer to a memory location
 * @param  -  base : base to be converted to
 * @return -  none
 *
 **************************************************************************************************/

void my_itoa(int32_t data,uint8_t* ptr, uint32_t base);


#endif /* INCLUDES_CONVERSION_H_ */
