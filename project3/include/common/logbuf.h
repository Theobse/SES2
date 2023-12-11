
/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file circbuf.h
 * @brief This  header file includes Circular Buffer functions declarations
 * @date October 20, 2017
 *
 * long description - The circbuf.c file includes functions declarations to -
 *                      1) add data to circular buffer(CB_buffer_add_item())
 *                      2) remove data from circular buffer (CB_buffer_remove_item())
 *                      3) check whether or not buffer is full(CB_is_full())
 *                      4) check whether or not buffer is empty(CB_is_empty())
 *                      5) peek at a location from head (CB_peek())
 *                      6) initialize circular buffer (CB_init())
 *                      7) destroy a circular buffer (CB_destroy())
 *
 *
 ************************************************************************************************/

#ifndef SOURCES_LOGBUF_H_
#define SOURCES_LOGBUF_H_

/*----- Header-Files -------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MKL25Z4.h"

/*----- Circular Buffer Struct --------------------------------------------*/

typedef struct{
uint8_t *buffer;
uint8_t *buffer_end;
uint8_t *head;
uint8_t *tail;
uint16_t length;
uint8_t count;
}Log_t;

/*----- Enum for Circular Buffer and UART ---------------------------------*/


typedef enum{
LOG_BUFFER_FULL=11,
LOG_BUFFER_EMPTY=80,
LOG_SUCCESS=13,
LOG_NULL_ERROR=0,
LOG_PEEK_LENGTH_ERROR=15,
LOG_TX_SUCCESS=16,
LOG_RX_SUCCESS=17,
LOG_TX_IRQ=18,
LOG_RX_IRQ=19
}Log_Buffer_Status;

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

/******************************** CB_buffer_add_item() function declaration ***********************************/

Log_Buffer_Status Log_buffer_add_item(Log_t *log, volatile uint8_t *data);

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

/******************************** CB_buffer_remove_item() function declaration ***********************************/

Log_Buffer_Status Log_buffer_remove_item(Log_t *log, volatile uint8_t *data);

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

/******************************** CB_is_full() function declaration ***********************************/

//Log_Buffer_Status Log_buffer_is_full(Log_t *log);
__attribute__((always_inline)) static inline Log_Buffer_Status Log_buffer_is_full(Log_t *log)
{
    if (log->count == log->length)
        return LOG_BUFFER_FULL;
    else
        return LOG_NULL_ERROR;
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

/******************************** CB_is_empty() function declaration ***********************************/

//Log_Buffer_Status Log_buffer_is_empty(Log_t *log);

__attribute__((always_inline)) static inline Log_Buffer_Status Log_buffer_is_empty(Log_t *log)
{
    if (log->count == 0)
        return LOG_BUFFER_EMPTY;
    else
        return LOG_NULL_ERROR;
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

/******************************** CB_peek() function declaration ***********************************/

Log_Buffer_Status Log_buffer_peek(Log_t *log, uint8_t peek_pos, uint8_t *peek_ptr);

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

/******************************** CB_init() function declaration ***********************************/

Log_Buffer_Status Log_buffer_init(Log_t *log, uint16_t length);

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

/******************************** CB_destroy() function declaration *********************************/
Log_Buffer_Status Log_buffer_destroy(Log_t *log);




#endif /* SOURCES_LOGBUF_H_ */
