/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file debug.h
 * @brief This file includes memory print function declarations.
 * @date October 1, 2017
 *
 * long description - The debug.h file includes memory print function declaration.
 *
 *
 ***************************************************************************************************/

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

/************* including standard libraries*************/

#include <stdio.h>
#include <stdint.h>
#include <math.h>

/*******************************************************/


/********************************** print_memory() *************************************************
 *
 * @name  print_memory(uint8_t *start, uint32_t length)
 * @brief function to print bytes from a memory location.
 * @param 1) *start - pointer to a memory location to print bytes
 *        2) length - variable to specify length of bytes.
 *
 * long description - This function takes a pointer to memory and prints the hex output of bytes
 *                    given a pointer to a memory location and a length of bytes to print.
 * @return void
 *
 *************************************************************************************************/

/**************************** print_memory() function declaration ************************************/

void print_memory(uint8_t *start, uint32_t length);

/*****************************************************************************************************/

#endif // DEBUG_H_INCLUDED
