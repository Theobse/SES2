/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file conversion.c
 * @brief This file includes data conversion functions
 * @date October 2, 2017
 *
 * long decription - The conversion.c file includes data conversion function for -
 *                      1) integer to ascii string (my_itoa())
 *
 ***************************************************************************************************/

/************* including header** libraries*************/

#include "conversion.h"

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

/*********************************** my_itoa function definition **************************************/


uint8_t my_itoa(int32_t data,uint8_t* ptr, uint32_t base)
{
    if((base<17)&&(base>1)) // condtion to run for base 2 to 16 only.
    {
       uint8_t s = 0; // variable s initialized for storing characters at ptr.
        uint32_t l=0; //  variable l initialized to determine length of string.

       if(data==0) // condition to check for zero.
       {
           *ptr =48; // ascii value in decimal for '0'
           l=l+1; //incrementing l
           return l;
       }

       if(data>0) // condition to check for positive number
       {
           *ptr = 43; // ascii value in decimal for '+'
           data = data; // no inversion if data is positive.
           l=l+1; // incrementing l

       }

       else if(data<0) // condition to check for negative number.
       {
           *ptr = 45; // ascii value in decimal for '-'
           data = -data; // inversion if data is negative.
           l=l+1; // incrementing l
       }


       while(data != 0) // condition to check for zero after each division.
       {
            ptr++; // incrementing ptr to store remainder in next memory location.
            s = data%base; //taking modulus to obtain new remainder.
            if(s>9) // condition to check if remainder is greater than 9
            {
               s = s - 9; // conversion of remainder to corresponding ascii value in decimal.
               s = s + 64; // 64 is ascii value of 'A'
            }
            else // condition for remainder between 0-9.
            {
               s = s + 48; // conversion of remainder to corresponding ascii value in decimal.
            }

            *ptr = s; // storing decimal ascii value of corresponding remainder in *ptr
            data = data/base; // Dividing the number(data) by base.
            l++; // incrementing l
       }

        ptr = ptr - l; // decrementing ptr by l to point initial memory location.

        uint8_t t; // variable t initialized for swapping data in *ptr.

        uint8_t i=2,j=l; //variables initialized for loop condition.

        while(i<j) // condition for swapping
        {
            t= *(ptr+i);
            *(ptr+i)=*(ptr+j);
            *(ptr+j)=t;
            i++;
            j--;
        }

        return l; //return length(l) of final ascii string.
    }

    else // condition for invalid base.
    {
        printf("\nError: Invalid parameters\n");
        return 0;
    }
}
