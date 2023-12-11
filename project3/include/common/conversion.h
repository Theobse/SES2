/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file conversion.h
 * @brief This file includes data conversion functions
 * @date October 2, 2017
 *
 * long decription - The conversion.c file includes data conversion function for -
 *                      1) integer to ascii string (my_itoa())
 *
 ***************************************************************************************************/

#ifndef SOURCES_CONVERSION_H_
#define SOURCES_CONVERSION_H_

/************* including standard libraries*************/

#include <stdio.h>
#include <stdint.h>
#include "project3.h"

/*******************************************************/

/********************************** my_itoa() **********************************************************
 *
 * @name  my_itoa(int32_t data,uint8_t* ptr, uint32_t base)
 * @brief function to convert a signed 32-bit integer to an ascii string and store it at memory loaction
 * @param 1) data - signed 32-bit integer in decimal.
 *        2) *ptr - pointer to a memory location.
 *        3) base - base to which data is converted.
/******************************************************************************************************/

uint8_t my_itoa(int32_t data,uint8_t* ptr, uint32_t base);

#endif /* SOURCES_CONVERSION_H_ */
