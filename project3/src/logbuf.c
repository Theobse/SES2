/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
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

#include "logbuf.h"

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

Log_Buffer_Status Log_buffer_add_item(Log_t *log, volatile uint8_t *data)
{
    if(log->count==log->length)
    {
        return LOG_BUFFER_FULL;
    }
    else if(log->head==log->buffer_end && log->count<log->length)
    {
        log->head=log->buffer;
        *(log->head)=*data;
        log->count++;
        log->head++;
        return LOG_SUCCESS;
    }
    else
    {
        *(log->head)=*data;
        log->count++;
        log->head++;
        return LOG_SUCCESS;
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

Log_Buffer_Status Log_buffer_remove_item(Log_t *log, volatile uint8_t *data)
{
    if(log->count==0)
    {
        return LOG_BUFFER_EMPTY;
    }
    else if(log->head==log->buffer && log->tail==log->buffer)
    {
        *data=*(log->tail);
        log->count--;
        return LOG_SUCCESS;
    }

    else if(log->tail==log->buffer_end)
    {
        *data=*(log->tail);
        log->tail=log->buffer;
        log->count--;
        return LOG_SUCCESS;
    }
    else
    {
        *data=*(log->tail);
        log->tail++;
        log->count--;
        return LOG_SUCCESS;
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

//Log_Buffer_Status Log_buffer_is_full(Log_t *log)


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
//Log_Buffer_Status Log_buffer_is_empty(Log_t *log)



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

Log_Buffer_Status Log_buffer_peek(Log_t *log, uint8_t peek_pos, uint8_t *peek_ptr)
{
    if(((log->count) != 0) && (peek_pos <= (log->length)))
    {
        if(((log->head)+(peek_pos))<(log->buffer_end))
        {
            *peek_ptr= *((log->head)+(peek_pos));
        }

        else if(((log->head)+(peek_pos))>=(log->buffer_end))
        {
            *peek_ptr= *((log->buffer)+((log->buffer_end)-((log->head)+(peek_pos))));
        }

        return LOG_SUCCESS;
    }
    else if((log->count) == 0)
    {
        return LOG_BUFFER_EMPTY;
    }
    else
    {
        return LOG_PEEK_LENGTH_ERROR;
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

Log_Buffer_Status Log_buffer_init(Log_t *log, uint16_t length)
{
    log->buffer = (uint8_t*)malloc(sizeof(uint8_t)*length);
    log->buffer_end = log->buffer + (sizeof(uint8_t)*length);
    log->head = log->buffer;
    log->tail = log->buffer;
    log->count = 0;
    log->length = length;
    return LOG_SUCCESS;
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

Log_Buffer_Status Log_buffer_destroy(Log_t *log)
{
    free(log->buffer);
    return LOG_SUCCESS;
}

