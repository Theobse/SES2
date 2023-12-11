/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file conversion.h
 * @brief This header file includes data conversion function declarations.
 * @date October 2, 2017
 *
 * long decription - The conversion.c file includes data conversion functions for -
 *                      1) integer to ascii string (my_itoa())
 *                      2) ascii string to 32-bit signed integer (my_atoi())
 *                      3) little endian to big endian (little_to_big32())
 *                      4) big endian to little endian (big_to_little32())
 *
 ***************************************************************************************************/

#ifndef INCLUDES_CONVERSION_H_
#define INCLUDES_CONVERSION_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/*******************************************************/

/********************************** my_itoa() **********************************************************
 *
 * @name  my_itoa(int32_t data,uint8_t* ptr, uint32_t base)
 * @brief function to convert a signed 32-bit integer to an ascii string and store it at memory loaction
 * @param 1) data - signed 32-bit integer in decimal.
 *        2) *ptr - pointer to a memory location.
 *        3) base - base to which data is converted.
 *
 * long description - This function converts a standard decimal integer (base 10) to number
 *                    of specified base. The sign of the decimal number(data)is first determined
 *                    specified memory location (*ptr). The remainder after taking modulus with base
 *                    and then stored at (using % operator) is converted to ascii character and
 *                    stored at next memory location (*(ptr + 1)). A variable 'l' is initialized to
 *                    zero and incremented to determine the length of string. The decimal number is
 *                    then divided until it becomes zero. After each modulus operation, ptr is
 *                    incremented and remainder is stored in *ptr. The characters stored in memory
 *                    locations - (ptr + 1) to (ptr + l) are reversed in order to store the ascii
 *                    string in correct format. Lastly, the length of the ascii string (including
 *                    sign) 'l' is returned by the function.
 *
 * @return length of ascii string (uint8_t l)
 *
 ******************************************************************************************************/

/*********************************** my_itoa function declaration **************************************/

void my_itoa(int32_t data,uint8_t* ptr, uint32_t base);


/******************************************************************************************************/


/********************************** my_atoi() *****************************************************
 *
 * @name  my_atoi(uint8_t* ptr, uint8_t digits, uint32_t base)
 * @brief function to convert an ascii string to a signed 32-bit integer.
 * @param 1) *ptr - pointer to a memory location.
 *        2) digits - length of ascii string(including sign).
 *        3) base - base to which data is converted.
 *
 * long description - This function converts an ascii string (number of specified base stored
 *                    as an ascii string at the specified memory location(*ptr)) to a signed
 *                    32-bit integer(int32_t value). The sign of the number is determined
 *                    by comparing data at ptr location. Data is read from consecutive memory
 *                    locations (from (ptr+1) to (ptr + digits) and converted to decimal integer
 *                    ( by multiplying base^n to each number read from memory location and adding
 *                    them). Finally, the signed decimal integer is returned by the function.
 *
 * @return signed 32-bit integer in decimal (int32_t value)
 *
 *************************************************************************************************/

/******************* my_atoi function declaration **************************/

int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);

/***************************************************************************/

/********************************** little_to_big32() ********************************************
 *
 * @name  little_to_big32(uint32_t *data, uint32_t length)
 * @brief function to convert little endian to big endian.
 * @param 1) *data - pointer to a memory location.
 *        2) length - length of ascii string(including sign).
 *
 * long description - This function converts data stored at memory locations (from (data) to
 *                    (data + length -1)) from little endian to big endian format for a 32-bit
 *                    word size. Each byte value is stored in uint8_t variable (a1,a2,a3,a4 to
 *                    break and shift the 32-bit data at memory location((data + b)). After each
 *                    conversion memory location is incremented till the data of all bytes is
 *                    converted.
 *
 * @return 0 if function is executed successfully.
 *
 *************************************************************************************************/

/***************************** little_to_big32 function declaration ********************************/

uint32_t *little_to_big32(uint32_t *data, uint32_t length);

/********************************** big_to_little32() ********************************************
 *
 * @name  big_to_little32(uint32_t *data, uint32_t length)
 * @brief function to convert big endian to little endian.
 * @param 1) *data - pointer to a memory location.
 *        2) length - length of ascii string(including sign).
 *
 * long description - This function converts data stored at memory locations (from (data) to
 *                    (data + length -1)) from big endian to little endian format for a 32-bit
 *                    word size. Each byte value is stored in uint8_t variable (a1,a2,a3,a4 to
 *                    break and shift the 32-bit data at memory location((data + b)). After each
 *                    conversion memory location is incremented till the data of all bytes is
 *                    converted.
 *
 * @return 0 if function is executed successfully.
 *
 *************************************************************************************************/

/***************************** big_to_little32 function declaration ********************************/

uint32_t *big_to_little32(uint32_t *data, uint32_t length);


/*************************************************************************************************/

#endif /* INCLUDES_CONVERSION_H_ */
