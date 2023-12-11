/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file memory.c
 * @brief This file includes memory manipulation function declarations.
 * @date October 1, 2017
 *
 * long decription - The memory.h file includes memory manipulation function declarations for -
 *                      1) moving bytes of data from source to destination(my_memmove())
 *                      2) copying bytes of data from source to destination(my_memcpy())
 *                      3) setting bytes of data to a specified value(my_memset())
 *                      4) setting bytes of data to zero(my_memzero())
 *                      5) reversing bytes of data at a specified memory loaction(my_reverse())
 *                      6) reserving a specified number of words at a particular
 *                         memory location.(reserve_words())
 *                      7) free a dynamic memory allocation by providing the pointer src to
 *                         the function(free_words())
 *
 ***************************************************************************************************/

#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

/************* including standard libraries*************/

#include <stdio.h>
#include <stdint.h>
#include <math.h>

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
 *                    is an overlap. Copy occurs with no data corruption. Finally, the function
 *                    returns destination location
 *

 *
 * @return dst - destination location.
 *
 *************************************************************************************************/

/**************************** my_memmove() function declaration **********************************/

uint8_t *my_memmove(uint8_t * src, uint8_t * dst, size_t length);

/********************************** my_memcpy() *************************************************
 *
 * @name  *my_memmove(uint8_t * src, uint8_t * dst, size_t length)
 * @brief function to move length of bytes data from source to destination.
 * @param 1) *src - pointer to a source memory location.
 *        2) *dst - pointer to a destination memory location
 *        3) length - length of data bytes to be moved.
 *
 * long description - This function takes two byte pointers (one source and one destination)
 *                    and a length of bytes to copy from the source location (src) to the
 *                    destination(dst). Data is copied from source location(src) to destination
 *                    location(dst).Is there is an overlap in source(src) and detination(dst)
 *                    memory locations, copy occurs but the data corrupts. Finally, the function
 *                    returns destination location
 *

 *
 * @return dst - destination location.
 *
 *************************************************************************************************/

uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length);


/********************************** my_memset() *************************************************
 *
 * @name  my_memset(uint8_t * src, size_t length, uint8_t value)
 * @brief function to set a length of  data bytes to a specified value
 * @param 1) *src - pointer to a source memory location.
 *        2) length - length of data bytes to be set to the specified value.
 *        3) value - value to be set for each byte
 *
 * long description - This function takes a pointer to a source memory location(src) and
 *                    a consecutive length in bytes are set to the specified value. The function
 *                    returns a pointer to the source(src).
 *
 * @return src - source location.
 *
 *************************************************************************************************/

/**************************** my_memset() function declaration ************************************/

int8_t * my_memset(uint8_t * src, size_t length, uint8_t value);

/********************************** my_memzero() *************************************************
 *
 * @name  my_memzero(uint8_t * src, size_t length)
 * @brief function to set a length of  data bytes zero.
 * @param 1) *src - pointer to a source memory location.
 *        2) length - length of data bytes to be set to zero.
 *
 * long description - This function takes a pointer to a source memory location(src) and
 *                    a consecutive length in bytes are set to zero. The function
 *                    returns a pointer to the source(src).
 *
 * @return src - source location.
 *
 *************************************************************************************************/

/**************************** my_memzero() function declaration ************************************/

uint8_t * my_memzero(uint8_t * src, size_t length);

/********************************** my_reverse() *************************************************
 *
 * @name  my_reverse(uint8_t * src, size_t length)
 * @brief function to reverse a length of data bytes.
 * @param 1) *src - pointer to a source memory location.
 *        2) length - length of data bytes to be reversed.
 *
 * long description - This function takes a pointer to a source memory location(src) and
 *                    a consecutive length in bytes are reversed. The function
 *                    returns a pointer to the source(src) if successfully executed.
 *
 * @return src - source location if reverse is successful else returns 0.
 *
 *************************************************************************************************/

/**************************** my_reverse() function declaration ************************************/

uint8_t * my_reverse(uint8_t * src, size_t length);

/********************************** reserve_words() *************************************************
 *
 * @name  reserve_words(size_t length)
 * @brief function to reserve a length of bytes.
 * @param length - length of bytes to be reserved.
 *
 *
 * long description - This function takes a pointer to a memory location(temp) and
 *                    a specified length in bytes are reserved using 'malloc' function.
 *                    The function returns a pointer to the memory location(temp).
 *
 * @return temp - memory location for reserved bytes.
 *
 *************************************************************************************************/

/**************************** reserve_words() function declaration ************************************/

uint8_t * reserve_words(size_t length);

/********************************** free_words() *************************************************
 *
 * @name  free_words(uint32_t * src)
 * @brief function to free a dynamic memory allocation.
 * @param *src - pointer to source memory location.
 *
 *
 * long description - This function frees a dynamic memory allocation by providing the pointer src to
 *                    the function
 *
 * @return void
 *
 *************************************************************************************************/

/**************************** freee_words() function declaration ************************************/

void free_words(uint32_t * src);

#endif // MEMORY_H_INCLUDED
