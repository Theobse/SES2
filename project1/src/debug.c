/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file debug.c
 * @brief This file includes memory print function.
 * @date October 1, 2017
 *
 * long description - The debug.c file includes memory print function to print the hex output of length
 *                   of bytes from a specified memory location.
 *
 *
 ***************************************************************************************************/

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

/**************************** print_memory() function definition ************************************/

void print_memory(uint8_t *start, uint32_t length)
{
    uint8_t a = 0; // variable a declared and initialized for loop condition
    printf("\n\n");
    while(a < length) // loop condition to check print untill specified length
    {
        printf("%x",*(start + a)); // printing each byte in hex format
        a++; // incrementing a
    }
}

//#endif // DEBUG_H_INCLUDED
