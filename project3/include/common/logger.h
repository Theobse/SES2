/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file logger.h
 * @brief This file includes function declarations for logging functions
 * @date November 23, 2017
 *
 * long description - The logger.h file includes functions to -
 *                      1) pass log structure to log buffer(log_pass())
 *                      2) determine log id and pass appropriate payload (log_id())
 *                      3) log string of characters (log_item())
 *                      4) remove (flush) log buffer data and send it by UART channel (log_flush())
 *                      5) log string of characters (log_string())
 *                      6) log a length of data bytes (log_data())
 *                      7) log an integer (log_int())
 *                      8) send string of data through UART channel (uart_flush())
 *
 *
 ***************************************************************************************************/

#ifndef SOURCES_LOGGER_H_
#define SOURCES_LOGGER_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include <stdlib.h>
#include "logbuf.h"
#include "uart.h"
#include "conversion.h"
#include "project3.h"
#include "spi.h"


#define LOG(id,str)							(log_id(id,str))
#define LOG_DATA(data,length)			(log_data(*data,length))
#define LOG_STRING(str)					(log_string(*str))
#define LOG_INT(num)					(log_int(num))
#define LOG_FLUSH()						(log_flush())

extern Log_t log_buffer;
extern uint8_t Log_Tx_Data;


/*******************************enum for LOG IDs*************************/

typedef enum{
	LOG_INITIALIZED = 100,
	GPIO_INITIALIZED,
	SYSTEM_INITIALIZED,
	SYSTEM_HALTED,
	INFO,
	WARNING,
	ERROR,
	PROFILING_STARTED,
	PROFILING_RESULT,
	PROFILING_COMPLETED,
	DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	DATA_NUMERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYSIS_COMPLETED,
	HEARTBEAT,
	DATA_INPUT_DISABLED,
	DATA_INPUT_ENABLED
}Log_Status;


/***********************Structure for Logger*****************************/

typedef struct{

	Log_Status log_id0;
	uint32_t timestamp;
	uint16_t len_payload;
	uint8_t *payload;
	uint16_t checksum;

}Log_Struct;

/********************************** log_pass()**********************************************************
 *
 * @name   -  log_pass()
 * @brief  -  function to passes log structure to log buffer
 * @param  -  id0 : enum for loggger status id
 * @param  -  *log_payload: pointer to payload
 * @param  -  length: length of payload
 *
 * long description - This function passes log struct to log buffer.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** log_pass() function declaration ***********************************/
void log_pass(Log_Status id0,uint8_t *log_payload, uint8_t length);

/************************************** log_id()**********************************************************
 *
 * @name   -  log_id()
 * @brief  -  function to determine log id and pass appropriate payload
 * @param  -  id: enum for loggger status id
 * @param  -  str: payload pointer
 *
 * long description - This function determine log id and pass appropriate payload.
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************* log_id() function declaration *************************************/

void log_id(Log_Status id,uint8_t *str);

/********************************** log_item()**********************************************************
 *
 * @name   -  log_item()
 * @brief  -  function to add log struct to log buffer
 * @param  -  *ab: pointer to log structure
 *
 * long description - This function adds log struct to log buffer.
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************* log_item() function declaration ***********************************/

void log_item(Log_Struct *ab);

/********************************** log_flush()**********************************************************
 *
 * @name   -  log_flush()
 * @brief  -  function to remove (flush) log buffer data and send it by UART channel.
 * @param  -  void
 *
 * long description - This function removes (flush) log buffer data and send it by UART channel
 *                    in blocking mode.
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ log_flush() function declaration ***********************************/


void log_flush(void);

/********************************** log_string()**********************************************************
 *
 * @name   -  log_string()
 * @brief  -  function to log string of characters
 * @param  -  *str: pointer to string
 *
 * long description - This function logs string of characters
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************* log_string() function declaration ***********************************/

void log_string(uint8_t *str);

/********************************** log_data()**********************************************************
 *
 * @name   -  log_data()
 * @brief  -  function to log a length of data bytes
 * @param  -  *data: pointer to log structure
 * @param  -  length: length of bytes
 *
 * long description - This function logs a length of data bytes.
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************* log_data() function declaration ***********************************/

void log_data(uint8_t *data, uint8_t length);

/********************************** log_int()**********************************************************
 *
 * @name   -  log_int()
 * @brief  -  function to log an integer
 * @param  -  num: integer to be logged
 *
 * long description - This function logs integer.
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************* log_int() function declaration ************************************/

void log_int(int32_t num);

/********************************** uart_flush()**********************************************************
 *
 * @name   -  uart_flush()
 * @brief  -  function to send string of data through UART channel
 * @param  -  *str: pointer to string of data
 *
 * long description - This function sends string of data through UART channel
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************* uart_flush() function declaration ************************************/

void uart_flush(uint8_t *str);



#endif /* SOURCES_LOGGER_H_ */
