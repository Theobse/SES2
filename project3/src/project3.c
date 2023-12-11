/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file project3.c
 * @brief This file includes logging functions
 * @date December 3, 2017
 *
 * long description - The logger.c file includes functions to -
 *                      1) project3() to initialise logging functions
 *                      2) data() to log data receive and data analysis
 *                      3) profiling() to perform profiling function on library, NON-DMA and DMA
 *                         memmove and memmset functions
 *
 ***************************************************************************************************/

#include "project3.h"


/*----- Global Variables ------------------------------------- -------------*/

uint8_t Rx_Data;
uint8_t Tx_Data;
uint8_t Rxd_Data;

uint8_t character_count[4]={0,0,0,0};
uint8_t char_str[4][10];
uint8_t *num = &char_str[0][0];
uint8_t *alpha = &char_str[1][0];
uint8_t *punc = &char_str[2][0];
uint8_t *misc = &char_str[3][0];
uint8_t time[4];
uint32_t start_time;
uint32_t end_time;
uint8_t t;


/*********************************** project3() **********************************************************
 *
 * @name   -  project3()
 * @brief  -  function to pass logs to log buffer and then print it to terminal through terminal
 *
 * long description - This function takes data input from user and depending on the received data
 * 						it performs various logging functions such as data analysis and profiling
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** project3() function definition ***********************************/

void project3()
{
	SystemInit();								//Initialize System
	int i;
	for(i=0;i<10;i++)
	{
		*(num+i)=0;
		*(alpha+i)=0;
		*(punc+i)=0;
		*(misc+i)=0;
	}
	log_mode = NON_BLOCKING_MODE;				//selest blocking or non-blocking mode for logger

	CB_init(&Rx_Buffer,50);						//Initialize Receive buffer

	RTC_init();									//Initialize RTC
	UART_configure();							//Initialize UART

	while(1)
	{
		CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);
		if(Rxd_Data==61)						//if received data is '=' then initialize LOG
		{
			Log_buffer_init(&log_buffer,500);	//initialize log buffer to transmit data to terminal through UART
			Rxd_Data=0;
			LOG(LOG_INITIALIZED,NULL);			//log LOG INITIALIZED to terminal
			LOG(SYSTEM_INITIALIZED,NULL);		//log SYSTEM INITIALIZED to terminal
			GPIO_nrf_init();					//Initialize GPIO
			RTC_IER |= RTC_IER_TSIE(1); 		//Seconds interrupt enable

			while(1)
			{
				CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);
				if(Rxd_Data==47)				//if received data is '/' then initialize DATA INPUT
				{
					RTC_IER &= ~RTC_IER_TSIE(1); 	//Seconds interrupt disable
					Rxd_Data=0;
					LOG(DATA_INPUT_ENABLED,NULL);	//log DATA INPUT ENABLED to terminal
					data();
					RTC_IER |= RTC_IER_TSIE(1); 	//Seconds interrupt enable
				}

				if(Rxd_Data==46)				//if received data is '.' then initialize PROFILING
				{
					RTC_IER &= ~RTC_IER_TSIE(1); 	//Seconds interrupt disable
					Rxd_Data=0;
					LOG(PROFILING_STARTED,NULL);	//log PROFILING STARTED to terminal
					profiling();
					RTC_IER |= RTC_IER_TSIE(1); 	//Seconds interrupt enable
				}

				if(Rxd_Data==61)				//if received data is '=' then STOP LOGGING
				{
					RTC_IER &= ~RTC_IER_TSIE(1); 	//Seconds interrupt disable
					Rxd_Data=0;
					break;
				}
			}

			LOG(SYSTEM_HALTED,NULL);			//log SYSTEM HALTED to terminal
			Log_buffer_destroy(&log_buffer);
		}

		if(Rxd_Data==44)						//if received data is ',' then show results of profiling
		{
			profile_test();
		}

		if(Rxd_Data==39)						//if received data is ''' then show results of SPI_NRF
		{
			spi_nrf_test();
		}
	}
}

/************************************ data() **********************************************************
 *
 * @name   -  data()
 * @brief  -  function to perform data analysis on the data received through uart
 *
 * @return -  void
 *
 ******************************************************************************************************/

/************************************ data() function definition ***********************************/

void data()
{
	while(1)
	{

    	//----- Removing Data from Rx Buffer  -------------------------------------------- ------

		CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);

	   	//----- Check for Numeric characters  -------------------------------------------- ------
		if((Rxd_Data>47) && (Rxd_Data<58))
	    {
			LOG(DATA_RECEIVED,NULL);			//log DATA RECEIVED to terminal
			character_count[0]++;
			*num = Rxd_Data;
			num++;
			Rxd_Data=0;
	    }

	    //----- Check for Alphabetic characters  ----------------------------------------- ------

		else if(((Rxd_Data>64) && (Rxd_Data<91))||((Rxd_Data>96) && (Rxd_Data<123)))
	    {
			LOG(DATA_RECEIVED,NULL);			//log DATA RECEIVED to terminal
			character_count[1]++;
			*alpha = Rxd_Data;
			alpha++;
			Rxd_Data=0;
	    }

	    //----- Check for Punctuation characters  ----------------------------------------- ----

		else if(((Rxd_Data>32) && (Rxd_Data<46))||((Rxd_Data>57) && (Rxd_Data<61))||((Rxd_Data>90) && (Rxd_Data<97))||((Rxd_Data>122) && (Rxd_Data<127)))
		{
			LOG(DATA_RECEIVED,NULL);			//log DATA RECEIVED to terminal
			character_count[2]++;
			*punc = Rxd_Data;
			punc++;
			Rxd_Data=0;
		}

	    //----- Check for Tab character - ------------------------------------------------ ------

		else if(Rxd_Data==9)					//if received data is 'TAB' then start data analysis
	    {
			num = &char_str[0][0];
			alpha = &char_str[1][0];
			punc = &char_str[2][0];
			misc = &char_str[3][0];
			LOG(DATA_ANALYSIS_STARTED,NULL);	//log DATA ANALYSIS STARTED to terminal
			LOG(DATA_ALPHA_COUNT,NULL);			//log DATA ALPHA COUNT to terminal
			LOG(DATA_NUMERIC_COUNT,NULL);		//log DATA NUMERIC COUNT to terminal
			LOG(DATA_PUNCTUATION_COUNT,NULL);	//log DATA PUNCTUATION COUNT to terminal
			LOG(DATA_MISC_COUNT,NULL);			//log DATA MISC COUNT to terminal
			character_count[0]=0;
			character_count[1]=0;
			character_count[2]=0;
			character_count[3]=0;
			LOG(DATA_ANALYSIS_COMPLETED,NULL);	//log DATA ANALYSIS COMPLETED to terminal
	        Rxd_Data=0;
	    }

		//----- Check for Miscellaneous characters  ---------------------------------------------

		else if(((Rxd_Data>90)&&(Rxd_Data<97))||(Rxd_Data==127)||(Rxd_Data==27))
	    {
			LOG(DATA_RECEIVED,NULL);			//log DATA RECEIVED to terminal
			character_count[3]++;
			*misc = Rxd_Data;
			misc++;
	        Rxd_Data=0;
	    }

		if(Rxd_Data==47)						//if received data is '/' then disable input
		{
			Rxd_Data=0;
			LOG(DATA_INPUT_DISABLED,NULL);
			break;
		}
	}
}

/************************************ profiling() **********************************************************
 *
 * @name   -  profiling()
 * @brief  -  function to perform profiling operation on library, NON-DMA and DMA memmove and memset functions
 *
 * @return -  void
 *
 ******************************************************************************************************/

/************************************ profiling() function definition ***********************************/
void profiling()
{
	while(1)
	{
		CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);
		if(Rxd_Data==49)						//if received data is '1' then start profiling for library memmove function
		{
			Rxd_Data=0;
			lib_memmove_test(10);
			LOG(INFO,"lib-memmove for 10 bytes");//log INFO to terminal
		}

		if(Rxd_Data==50)						//if received data is '2' then start profiling for library memset function
		{
			Rxd_Data=0;
			lib_memset_test(10);
			LOG(INFO,"lib-memset for 10 bytes");//log INFO to terminal
		}

		if(Rxd_Data==51)						//if received data is '3' then start profiling for NON-DMA memmove function
		{
			Rxd_Data=0;
			my_memmove_test(10);
			LOG(INFO,"my-memmove for 10 bytes");//log INFO to terminal
		}


		if(Rxd_Data==52)						//if received data is '4' then start profiling for NON-DMA memset function
		{
			Rxd_Data=0;
			my_memset_test(10);
			LOG(INFO,"my-memset for 10 bytes");	//log INFO to terminal
		}

		if(Rxd_Data==53)						//if received data is '5' then start profiling for DMA memmove function
		{
			Rxd_Data=0;
			dma_memmove_test(10);
			LOG(INFO,"dma-memmove for 10 bytes");//log INFO to terminal
		}

		if(Rxd_Data==54)						//if received data is '6' then start profiling for DMA memset function
		{
			Rxd_Data=0;
			dma_memset_test(10);
			LOG(INFO,"dma-memset for 10 bytes");//log INFO to terminal
		}

		if(Rxd_Data==48)						//if received data is '0' then stop profiling
		{
			Rxd_Data=0;
			LOG(PROFILING_COMPLETED,NULL);		//log INFO to terminal
			break;
		}
	}
}
