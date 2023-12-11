/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file memory.c
 * @brief This file includes memory manipulation functions
 * @date October 1, 2017
 *
 * long decription - The memory.c file includes memory manipulation functions for -
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

/************* including standard libraries*************/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


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

 /**************************** my_memmove() function definition **********************************/


uint8_t *my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
    if (src==NULL)
        return NULL;
    else
    {
    size_t i; // variable i declared for loop condition
    uint8_t *temp=malloc(length); // length of bytes allocated starting from temp
    for(i=0;i<length;i++) // loop condition to copy bytes of data from src to temp
    {
        *(temp+i)=*(src+i);//Copying each byte consecutively.
    }

    for(i=0;i<length;i++) // loop condition to copy bytes of data from temp to dst.
    {
        *(dst+i)=*(temp+i); // Copying each byte consecutively.
    }
    return dst; // Returning destination location.
    }
}


/**************************************************************************************************/


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

/**************************** my_memcpy() function definition ************************************/

uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length)
{
    int i; // variable i declared for loop condition.
    if (src == dst) // check if source and destination are same.
    {
        return dst;//return destination location.
    }
    else if(src > dst) // check if source location is before destination location.
    {
        for( i = 0; i < length-1; i ++) // loop condition to copy data from src to dst
        {
            *(dst+i) = *(src+i); // copying each byte of data consecutively from src to dst.

        }

    }
    else if(src < dst) // check if source location is after destination location.
    {
        for ( i = length-1; i >= 0; i--) // loop condition to copy data from src to dst
        {
            *(dst+i) = *(src+i); // copying each byte of data consecutively from src to dst.
        }
    }
    return dst; //return destination location.
}

/**************************************************************************************************/

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

/**************************** my_memset() function definition ************************************/

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value)
{
    int i; // variable i declared for loop condition
    if(src==NULL)
       return NULL;
    else
    {
  	for(i=0;i<length;i++) // loop condition to set a length of bytes to specified value.
    	{
            *(src+i)=value; //  setting each byte consecutively to the specified value.
    	}
    	return src;
    }
}


/*************************************************************************************************/

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

/**************************** my_memzero() function definition ************************************/


uint8_t * my_memzero(uint8_t * src, size_t length)
{
    int i; // variable i declared for loop condition
    if (src==NULL)
	return NULL;

    else
    {
    for(i=0;i<length;i++) // loop condition to set a length of bytes to zero.
    {
        *(src+i)=0; //  setting each byte consecutively to zero.
    }
    return src;
    }
}

/*************************************************************************************************/

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

/**************************** my_reverse() function definition ************************************/


uint8_t * my_reverse(uint8_t * src, size_t length)
{
    
    if(src == NULL)
     	return NULL;

    else
    {
    int i; // variable i declared for loop condition.
    size_t j=length; // variable j declared and initialized to length
    int k=0; // variable k declared and initialized to zero for checking length
    uint8_t *temp=malloc(j*sizeof(size_t)); // memory of size of integer value of j allocated.

    for(i=0;i<length;i++)
    {
        *(temp+i)=*(src+i); //consecutively copying each data byte from src to temp
    }

    for(i=0;i<length;i++)
    {
        j--;
        *(src+j)=*(temp+i); //consecutively copying each data byte from temp to src.
    }

    j=length; // assigning j the value of length

    for(i=0;i<length;i++)
    {
        j--;
        if(*(src+i)==*(temp+j)) //comparing data in reversed bytes
        {
            k++; // incrementing k for each successful comparison.
        }
    }

    if (k==length)
    {
        return src; // returning source location if data successfully reversed.
    }
    else return 0; // returning zero if not reversed successfully.
    }
}

/*************************************************************************************************/

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

/**************************** reserve_words() function definition ************************************/


uint8_t * reserve_words(size_t length)
{
    uint8_t *temp = malloc(length*sizeof(size_t)); // memory of length number of bytes allocated
                                                   // starting from temp location.

    return (temp); // returning temp memory location.
}


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

/**************************** freee_words() function definition ************************************/

void free_words(uint32_t * src)
{
    free(src);
}

/****************************************************************************************************/



