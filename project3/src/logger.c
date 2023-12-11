/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file logger.c
 * @brief This file includes logging functions
 * @date November 23, 2017
 *
 * long description - The logger.c file includes functions to -
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

#include "logger.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


Log_t log_buffer;
uint8_t Log_Tx_Data;

uint8_t log_tag[20][26] = 		   {"<LOG INITIALIZED>	",
									"<GPIO INITIALIZED>	",
									"<SYSTEM INITIALIZED>	",
									"<SYSTEM HALTED>   	",
									"<INFO>			",
									"<WARNING>			",
									"<ERROR>			",
									"<PROFILING STARTED>	",
									"<PROFILING RESULT>	",
									"<PROFILING COMPLETED>	",
									"<DATA RECIEVED>		",
									"<DATA ANALYSIS STARTED>	",
									"<DATA ALPHA COUNT>	 ",
									"<DATA NUMERIC COUNT> 	",
									"<DATA PUNCTUATION COUNT>",
									"<DATA MISC COUNT>	",
									"<DATA ANALYSIS COMPLETED>",
									"<HEARTBEAT>		",
									"<DATA INPUT DISABLED>	",
									"<DATA INPUT ENABLED>	"};

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

/*********************************** log_pass() function definition ***********************************/

void log_pass(Log_Status id0,uint8_t *log_payload, uint8_t length){

	//START_CRITICAL();
	Log_Struct log_struct;					// log structure declared
	log_struct.log_id0 = id0;				// log id
	log_struct.timestamp = RTC->TSR;		// getting timestamp by reading TSR register
	log_struct.payload = log_payload;		// passing log payload ptr
	log_struct.len_payload = length;		// passing length of payload

	log_item(&log_struct);					// calling log_item to add log structure to log buffer
	//END_CRITICAL();
	//log_flag = 0x78;
}

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

/************************************ log_flush() function definition ***********************************/

void log_flush(void){
	while(Log_buffer_is_empty(&log_buffer) != LOG_BUFFER_EMPTY){ //wait until log buffer is empty
		Log_buffer_remove_item(&log_buffer, &Log_Tx_Data);		 // write data to log_tx_data variable
		UART_send(&Log_Tx_Data);								 // Send log_tx_data through UART channel
	}
}

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

/************************************* log_id() function definition *************************************/


void log_id(Log_Status id,uint8_t *str){
	switch(id){
		case LOG_INITIALIZED:								//matching log id to pass the required payload
			log_pass(LOG_INITIALIZED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
		    break;

		case GPIO_INITIALIZED:
			log_pass(GPIO_INITIALIZED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
          break;

		case SYSTEM_INITIALIZED:
			log_pass(SYSTEM_INITIALIZED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
             break;

		case SYSTEM_HALTED:
			log_pass(SYSTEM_HALTED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case INFO:
			log_pass(INFO,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			delay();
			log_string(str);
			break;

		case WARNING:
			log_pass(WARNING,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			delay();
			log_string(str);
			break;

		case ERROR:
			log_pass(ERROR,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			delay();
			log_string(str);
			break;

		case PROFILING_STARTED:
			log_pass(PROFILING_STARTED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case PROFILING_RESULT:
			log_pass(PROFILING_RESULT,&time[1],3);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case PROFILING_COMPLETED:
			log_pass(PROFILING_COMPLETED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_RECEIVED:
			log_pass(DATA_RECEIVED,&Rxd_Data,1);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_ANALYSIS_STARTED:
			log_pass(DATA_ANALYSIS_STARTED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_ALPHA_COUNT:
			log_pass(DATA_ALPHA_COUNT,alpha,character_count[1]);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_NUMERIC_COUNT:
			log_pass(DATA_NUMERIC_COUNT,num,character_count[0]);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_PUNCTUATION_COUNT:
			log_pass(DATA_PUNCTUATION_COUNT,punc,character_count[2]);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_MISC_COUNT:
			log_pass(DATA_MISC_COUNT,misc,character_count[3]);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_ANALYSIS_COMPLETED:
			log_pass(DATA_ANALYSIS_COMPLETED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case HEARTBEAT:
			log_pass(HEARTBEAT,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_INPUT_DISABLED:
			log_pass(DATA_INPUT_DISABLED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		case DATA_INPUT_ENABLED:
			log_pass(DATA_INPUT_ENABLED,NULL,0);
			if(log_mode != 0x43){							// send data in blocking mode
				log_flush();}								//send data using log flush if interrupt mode is not enabled
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;				// disable  UART Tx interrupt
				UART0_C2 |= UART0_C2_TIE_MASK;}				// enable UART Tx interrupt
			break;

		default:
             break;
	}
}

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

/************************************* log_item() function definition ***********************************/

void log_item(Log_Struct *ab){

	uint8_t buffer[80];										//buffer to store ascii values and add them to log buffer
	uint8_t i;
	for(i=0;i<10;i++)
	{
		buffer[i]=0;
	}
	uint8_t checksum;										// checksum variable
	my_itoa(ab->timestamp,buffer,10);						// converts timestamp to ascii string and store in buffer
	i = 1;
			while(buffer[i] != 0){							//adding timestamp to log buffer
				Log_buffer_add_item(&log_buffer, &buffer[i]);
				checksum ^= buffer[i];						// calculating checksum
				i++;
				buffer[i-1] = 0;
			}
	for(i=0;i<10;i++)
	{
		buffer[i]=0;
	}
	i=' ';
	Log_buffer_add_item(&log_buffer,&i);
	uint8_t y;
	y = 0;
	y = (uint8_t)(ab->log_id0);
	my_itoa(y,buffer,10);

	i = '\t';
		Log_buffer_add_item(&log_buffer,&i);

	i = 0;
		while(log_tag[y-100][i] != 0){							// adding log tag to log buffer
			checksum ^= log_tag[y-100][i];
			Log_buffer_add_item(&log_buffer, &log_tag[y-100][i]);
			i++;
		}
	i = '\t';
	Log_buffer_add_item(&log_buffer,&i);


	i = 1;
		while(buffer[i] != 0){
			checksum ^= buffer[i];
			Log_buffer_add_item(&log_buffer, &buffer[i]);		//adding log id to log buffer
			i++;
			buffer[i-1] = 0;
		}
		for(i=0;i<10;i++)
		{
			buffer[i]=0;
		}
	//Log_buffer_add_item(&log_buffer, &bu);

	i='	';
	Log_buffer_add_item(&log_buffer,&i);

	if(ab->payload != NULL){									//pass payload and length only if payload is not null
		if(ab->log_id0==PROFILING_RESULT || ab->log_id0==DATA_RECEIVED)
		{
		//my_itoa(ab->len_payload,buffer,10);
		//i=1;
		while(buffer[i] != 0){
		//Log_buffer_add_item(&log_buffer, &buffer[i]);
		i++;
		//buffer[i-1] = 0;
		}
		i = ' ';
		Log_buffer_add_item(&log_buffer,&i);
		Log_buffer_add_item(&log_buffer,&i);
		}
		else
		{
			my_itoa(ab->len_payload,buffer,10);
			i=1;
			while(buffer[i] != 0){
				checksum ^= buffer[i];
			Log_buffer_add_item(&log_buffer, &buffer[i]);
			i++;
			//buffer[i-1] = 0;
		}
			for(i=0;i<10;i++)
			{
				buffer[i]=0;
			}
			i = ' ';
			Log_buffer_add_item(&log_buffer,&i);
			Log_buffer_add_item(&log_buffer,&i);
		}
		for(i=0;i<ab->len_payload;i++){
			checksum ^= *(ab->payload+i);
			Log_buffer_add_item(&log_buffer,ab->payload +i);
		}
	}

	else{
		i = ' ';
		Log_buffer_add_item(&log_buffer,&i);
		Log_buffer_add_item(&log_buffer,&i);
	}
	i = ' ';
	Log_buffer_add_item(&log_buffer,&i);
	Log_buffer_add_item(&log_buffer,&i);
	my_itoa(checksum,buffer,10);
	Log_buffer_add_item(&log_buffer,&buffer[1]);
	for(i=0;i<10;i++)
	{
		buffer[i]=0;
	}
	i = '   ';
	Log_buffer_add_item(&log_buffer,&i);

	if(ab->log_id0!=INFO){
		i='\r';
		Log_buffer_add_item(&log_buffer,&i);
		i='\n';
		Log_buffer_add_item(&log_buffer,&i);
		i='\r';
		Log_buffer_add_item(&log_buffer,&i);
		i='\n';
		Log_buffer_add_item(&log_buffer,&i);
		}
}

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

/************************************* log_string() function definition ***********************************/

void log_string(uint8_t *str){
	uint8_t d;
	uint8_t i;
	while(*str != 0){				// condition to send string data through UART channel
		d = *str;
		UART_send(&d);				// send string through UART
		str++;
	}
	i='\r';
	UART_send(&i);
	i='\n';
	UART_send(&i);
	i='\r';
	UART_send(&i);
	i='\n';
	UART_send(&i);
}

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

/************************************* log_data() function definition ***********************************/

void log_data(uint8_t *data, uint8_t length){
	uint8_t i = '\t';
	UART_send(&i);
	i = 0;
	uint8_t l;
	while(i<length){						// condition to send length of data bytes through UART channel
		l = *(data + i);
		UART_send(&l);
		i++;
	}
}

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

/************************************* log_int() function definition ************************************/

void log_int(int32_t num){
	uint8_t i = '\t';
	UART_send(&i);
	uint8_t buffer[10];
	uint8_t o = 1;
	my_itoa(num,buffer,10);
	while(buffer[o] != 0){						// condition to send integer ascii string through UART channel
		UART_send(&buffer[o]);
		o++;
	}
}

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

/************************************* uart_flush() function definition ************************************/

void uart_flush(uint8_t *str){
	uint8_t d;
	uint8_t i = '\t';
	UART_send(&i);
	while(*str != 0){				// send string through UART using polling
		d = *str;
		UART_send(&d);
		str++;
	}
}
