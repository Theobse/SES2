/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file conversion.c
 * @brief This file includes data conversion functions
 * @date October 2, 2017
 *
 * long decription - The conversion.c file includes data conversion functions for -
 *                      1) integer to ascii string (my_itoa())
 *                      2) ascii string to 32-bit signed integer (my_atoi())
 *                      3) little endian to big endian (little_to_big32())
 *                      4) big endian to little endian (big_to_little32())
 *
 ***************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>


/********************************** little_to_big32() ********************************************
 *
 * @name  *little_to_big32(uint32_t *data, uint32_t length)
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

/***************************** little_to_big32 function definition ********************************/

uint32_t *little_to_big32(uint32_t *data, uint32_t length)
{
    if(data==NULL)
   	return NULL;
    
    else
    {
    uint32_t b = 0; // variable b initialized for loop condition
    while(b < length) //loop condition for data conversion till all 32-bit words are converted.
    {
        uint32_t a = *(data + b); // variable a initialized to store data of *(data + b)

        int8_t a1,a2,a3,a4; //variables declared to break and shift 32-bit data in a
        a1 = (a & 0x000000ff); // a1 stores last byte of a
        a2 = (a & 0x0000ff00) >> 8; // a2 stores 3rd byte of a
        a3 = (a & 0x00ff0000) >> 16; //a3 stores 2nd byte of a
        a4 = (a & 0xff000000) >> 24; // a4 stores 1st byte of a

        a = ((a1<<24)|(a2<<16)|(a3<<8)|(a4)); //data shifted and bitwise OR operation performed.

        *(data + b) = a; //data after conversion stored in *(data+b)
        b++; //Incrementing b
    }
    return data;
    }
}


/*************************************************************************************************/


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

/***************************** big_to_little32 function definition ********************************/


uint32_t *big_to_little32(uint32_t *data, uint32_t length)
{
    if(data==NULL)
	return NULL;
 
    else
    {
    uint32_t a = 0;  // variable a initialized for loop condition
    while(a < length)  //loop condition for data conversion till all 32-bit words are converted.
    {
        uint32_t b = *(data + a); // variable b initialized to store data of *(data + a)

        int8_t b1,b2,b3,b4;  //variables declared to break and shift 32-bit data in b
        b1 = (b & 0xff000000) >> 24; // b1 stores 1st byte of b
        b2 = (b & 0x00ff0000) >> 16; // b2 stores 2nd byte of b
        b3 = (b & 0x0000ff00) >> 8; // b3 stores 3rd byte of b
        b4 = (b & 0x000000ff); // b4 stores last byte of b

        b = ((b1)|(b2<<8)|(b3<<16)|(b4<<24)); //data shifted and bitwise OR operation performed.

        *(data + a) = b; //data after conversion stored in *(data+a)
        a++; // Incrementing a
    }
    return data;
    }
}


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

void my_itoa(int32_t data,uint8_t* ptr, uint32_t base)
{
    if((base<17)&&(base>1)) // condtion to run for base 2 to 16 only.
    {
       uint8_t s = 0; // variable s initialized for storing characters at ptr.
        uint32_t l=0; //  variable l initialized to determine length of string.

       if(data==0) // condition to check for zero.
       {
           *ptr =48; // ascii value in decimal for '0'
           l=l+1; //incrementing l
           //return l;
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

        //return l; //return length(l) of final ascii string.
    }

    else // condition for invalid base.
    {
        printf("\nError: Invalid parameters\n");
        //return 0;
    }
}

