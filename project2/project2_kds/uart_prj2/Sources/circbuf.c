/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file circbuf.c
 * @brief This file includes Circular Buffer functions
 * @date October 20, 2017
 *
 * long description - The circbuf.c file includes functions to -
 *                      1) add data to circular buffer(CB_buffer_add_item())
 *                      2) remove data from circular buffer (CB_buffer_remove_item())
 *                      3) check whether or not buffer is full(CB_is_full())
 *                      4) check whether or not buffer is empty(CB_is_empty())
 *                      5) peek at a location from head (CB_peek())
 *                      6) initialize circular buffer (CB_init())
 *                      7) destroy a circular buffer (CB_destroy())
 *
 *
 ***************************************************************************************************/


/*----- Header-Files -------------------------------------------------------*/

#include "circbuf.h"


/********************************** CB_buffer_add_item() *****************************************************
 *
 * @name   -  CB_buffer_add_item()
 * @brief  -  function to add data to circular buffer
 * @param  -  *cb : pointer to circular buffer
 * @param  -  *data : data to be added to buffer
 *
 * long description - This function adds data to circular buffer from a given memory location.
 *
 * @return -  BUFFER_FULL : if buffer is full
 * @return -  SUCCESS : if data added successfully to buffer
 *
 ******************************************************************************************************/

/******************************** CB_buffer_add_item() function definition ***********************************/

CB_status CB_buffer_add_item(CB_t *cb, volatile uint8_t *data)
{
    if(cb->count==cb->length)
    {
        return BUFFER_FULL;
    }
    else if(cb->head==cb->buffer_end && cb->count<cb->length)
    {
        cb->head=cb->buffer;
        *(cb->head)=*data;
        cb->count++;
        cb->head++;
        return SUCCESS;
    }
    else
    {
        *(cb->head)=*data;
        cb->count++;
        cb->head++;
        return SUCCESS;
    }
}


/********************************** CB_buffer_remove_item() *****************************************************
 *
 * @name   -  CB_buffer_remove_item()
 * @brief  -  function to remove data from circular buffer
 * @param  -  *cb : pointer to circular buffer
 * @param  -  *data : location to which data is dumped from buffer.
 *
 * long description - This function removes data from circular buffer to a given memory location.
 *
 * @return -  BUFFER_EMPTY : if buffer is empty
 * @return -  SUCCESS : if data removed successfully from buffer
 *
 ******************************************************************************************************/

/******************************** CB_buffer_remove_item() function definition ***********************************/

CB_status CB_buffer_remove_item(CB_t *cb, volatile uint8_t *data)
{
    if(cb->count==0)
    {
        return BUFFER_EMPTY;
    }
    else if(cb->head==cb->buffer && cb->tail==cb->buffer)
    {
        *data=*(cb->tail);
        cb->count--;
        return SUCCESS;
    }

    else if(cb->tail==cb->buffer_end)
    {
        *data=*(cb->tail);
        cb->tail=cb->buffer;
        cb->count--;
        return SUCCESS;
    }
    else
    {
        *data=*(cb->tail);
        cb->tail++;
        cb->count--;
        return SUCCESS;
    }
}


/********************************** CB_is_full() *****************************************************
 *
 * @name   -  CB_is_full()
 * @brief  -  function to check whether or not buffer is full
 * @param  -  *cb : pointer to circular buffer
 *
 * long description - This function checks whether or not buffer is full.
 *
 * @return -  BUFFER_FULL : if buffer is full.
 * @return -  NULL_ERROR : if buffer is not full.
 *
 ******************************************************************************************************/

/******************************** CB_is_full() function definition ***********************************/

CB_status CB_is_full(CB_t *cb)
{
    if (cb->count == cb->length)
        return BUFFER_FULL;
    else
        return NULL_ERROR;
}


/********************************** CB_is_empty() *****************************************************
 *
 * @name   -  CB_is_empty()
 * @brief  -  function to check whether or not buffer is empty
 * @param  -  *cb : pointer to circular buffer
 *
 * long description - This function checks whether or not buffer is empty.
 *
 * @return -  BUFFER_EMPTY : if buffer is empty.
 * @return -  NULL_ERROR : if buffer is not empty.
 *
 ******************************************************************************************************/

/******************************** CB_is_empty() function definition ***********************************/

CB_status CB_is_empty(CB_t *cb)
{
    if (cb->count == 0)
        return BUFFER_EMPTY;
    else
        return NULL_ERROR;
}


/********************************** CB_peek() *****************************************************
 *
 * @name   -  CB_peek()
 * @brief  -  peek at a location from head
 * @param  -  *cb : pointer to circular buffer
 * @param  -  *peek_ptr : location to which data is dumped from buffer.
 * @param  -  peek_pos : position to peek from head
 *
 * long description - This function peeks at a location from head. The data of the peeked location
 * 					  is copied to peek pointer.
 *
 * @return -  BUFFER_EMPTY : if buffer is empty
 * @return -  SUCCESS : if data removed successfully from buffer
 * @return -  PEEK_LENGTH_ERROR : if data removed successfully from buffer
 *
 ******************************************************************************************************/

/******************************** CB_peek() function definition ***********************************/

CB_status CB_peek(CB_t *cb, uint8_t peek_pos, uint8_t *peek_ptr)
{
    if(((cb->count) != 0) && (peek_pos <= (cb->length)))
    {
        if(((cb->head)+(peek_pos))<(cb->buffer_end))
        {
            *peek_ptr= *((cb->head)+(peek_pos));
        }

        else if(((cb->head)+(peek_pos))>=(cb->buffer_end))
        {
            *peek_ptr= *((cb->buffer)+((cb->buffer_end)-((cb->head)+(peek_pos))));
        }

        return SUCCESS;
    }
    else if((cb->count) == 0)
    {
        return BUFFER_EMPTY;
    }
    else
    {
        return PEEK_LENGTH_ERROR;
    }

}


/********************************** CB_init() *****************************************************
 *
 * @name   -  CB_init()
 * @brief  -  function to create a circular buffer
 * @param  -  *cb : pointer to circular buffer
 * @param  -  length : size of buffer in bytes.
 *
 * long description - This function creates a circular buffer of specified bytes.
 *
 * @return -  SUCCESS : if buffer is successfully created.
 *
 ******************************************************************************************************/

/******************************** CB_init() function definition ***********************************/

CB_status CB_init(CB_t *cb, uint8_t length)
{
    cb->buffer = (uint8_t*)malloc(sizeof(uint8_t)*length);
    cb->buffer_end = cb->buffer + (sizeof(uint8_t)*length);
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
    cb->count = 0;
    cb->length = length;
    return SUCCESS;
}

/********************************** CB_destroy() *****************************************************
 *
 * @name   -  CB_destroy()
 * @brief  -  function to destroy a circular buffer
 * @param  -  *cb : pointer to circular buffer
 *
 * long description - This function destroys a circular buffer.
 *
 * @return -  SUCCESS : if buffer is successfully destroyed.
 *
 ******************************************************************************************************/

/******************************** CB_destroy() function definition ***********************************/
CB_status CB_destroy(CB_t *cb)
{
    free(cb->buffer);
    return SUCCESS;
}

