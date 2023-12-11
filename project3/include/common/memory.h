/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file memory.c
 * @brief This file includes memory manipulation functions
 * @date October 1, 2017
 *
 * long decription - The memory.c file includes memory manipulation functions for -
 *                      1) moving bytes of data from source to destination(my_memmove())
 *                      2) setting bytes of data to a specified value(my_memset())
 ***************************************************************************************************/

#ifndef SOURCES_MEMORY_H_
#define SOURCES_MEMORY_H_

/************* including header libraries***************/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "project3.h"

/*******************************************************/

/********************************** my_memmove() ********************************************
 *
 * @name  *my_memmove(uint8_t * src, uint8_t * dst, size_t length)
 * @brief function to move length of bytes data from source to destination.
 * @param 1) *src - pointer to a source memory location.
 *        2) *dst - pointer to a destination memory location
 *        3) length - length of data bytes to be moved.
 *
 * long description - This function takes two byte pointers (one source and one destination)
 *                    and a length of bytes to copy from the source location (src) to the
 *                    destination(dst). This is done by alloocating a length of bytes using
 *                    'malloc' function. Data is first copied to an intermediate location (temp)
 *                    from source location(src). Then the data is copied from temp to destination
 *                    location(dst).Thus, the data is copied from source to destination even if there
 *                    is an overlap. Copy occurs with no data corruption.
 *
 *************************************************************************************************/

void my_memmove(uint8_t *src, uint8_t *dst, uint32_t length);

/********************************** my_memset() *************************************************
 *
 * @name  my_memset(uint8_t * src, size_t length, uint8_t value)
 * @brief function to set a length of  data bytes to a specified value
 * @param 1) *src - pointer to a source memory location.
 *        2) length - length of data bytes to be set to the specified value.
 *        3) value - value to be set for each byte
 *
 * long description - This function takes a pointer to a source memory location(src) and
 *                    a consecutive length in bytes are set to the specified value.
 *
 *************************************************************************************************/

void my_memset(uint32_t value, uint8_t *dst, uint32_t length);

/********************************** my_memmove_optimized() ********************************************
 *
 * @name  *my_memmove_optimized(uint8_t * src, uint8_t * dst, size_t length)
 * @brief function to move length of bytes data from source to destination.
 * @param 1) *src - pointer to a source memory location.
 *        2) *dst - pointer to a destination memory location
 *        3) length - length of data bytes to be moved.
 *
 * long description - This function takes two byte pointers (one source and one destination)
 *                    and a length of bytes to copy from the source location (src) to the
 *                    destination(dst). This is done by alloocating a length of bytes using
 *                    'malloc' function. Data is first copied to an intermediate location (temp)
 *                    from source location(src). Then the data is copied from temp to destination
 *                    location(dst).Thus, the data is copied from source to destination even if there
 *                    is an overlap. Copy occurs with no data corruption.
 *
 *************************************************************************************************/

void my_memmove_optimized(uint8_t *src, uint8_t *dst, uint32_t length)__attribute__ ((optimize(3)));

/********************************** my_memset_optimized() *************************************************
 *
 * @name  my_memset(uint8_t * src, size_t length, uint8_t value)
 * @brief function to set a length of  data bytes to a specified value
 * @param 1) *src - pointer to a source memory location.
 *        2) length - length of data bytes to be set to the specified value.
 *        3) value - value to be set for each byte
 *
 * long description - This function takes a pointer to a source memory location(src) and
 *                    a consecutive length in bytes are set to the specified value.
 *
 *************************************************************************************************/


void my_memset_optimized(uint32_t value, uint8_t *dst, uint32_t length)__attribute__ ((optimize(3)));

#endif /* SOURCES_MEMORY_H_ */
