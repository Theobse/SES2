/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
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
 ***************************************************************************************************/

#ifndef INCLUDES_CIRCBUF_H_
#define INCLUDES_CIRCBUF_H_

/*----- Header-Files -------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*----- Circular Buffer Struct --------------------------------------------*/

typedef struct{
uint8_t *buffer;
uint8_t *buffer_end;
uint8_t *head;
uint8_t *tail;
uint8_t length;
uint8_t count;
}CB_t;

/*----- Enum for Circular Buffer and UART ---------------------------------*/
typedef enum{
BUFFER_FULL=1,
BUFFER_NOT_FULL=2,
BUFFER_EMPTY=3,
BUFFER_NOT_EMPTY=4,
SUCCESS=5,
FAILURE=6,
NULL_ERROR=7,
PEEK_LENGTH_ERROR=8,
TX_SUCCESS=9,
RX_SUCCESS=10,
TX_IRQ=11,
RX_IRQ=12
}CB_status;

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

CB_status CB_buffer_add_item(CB_t *cb, uint8_t *data);


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

CB_status CB_buffer_remove_item(CB_t *cb, uint8_t *data);

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

CB_status CB_is_full(CB_t *cb);

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

CB_status CB_is_empty(CB_t *cb);

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


CB_status CB_peek(CB_t *cb, uint8_t peek_pos, uint8_t *peek_ptr);

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

CB_status CB_init(CB_t *cb, uint8_t length);

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

/******************************** CB_destroy() function declaration ***********************************/

CB_status CB_destroy(CB_t *cb);

#endif /* INCLUDES_CIRCBUF_H_ */
