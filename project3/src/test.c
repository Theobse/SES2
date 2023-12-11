/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file test.c
 * @brief This file includes functions for testing profiling, spi and nrf
 * @date November 29, 2017
 *
 * long description - The test.c file includes functions to -
 *                      1) test profile time for memory functions dma,non-dma,stdlib) (profile_test())
 *                      2) test read and write operation to nrf module (spi_nrf_test())
 *                      3) test config read and write operation to nrf module (config_reg_test())
 *                      4) test read and write operation to nrf module (tx_addr_test())
 *                      5) test read and write operation to nrf module (rf_setup_test())
 *                      6) test read and write operation to nrf module (rf_ch_reg_test())
 *                      7) read the status register of nrf module (status_reg_test())
 *                      8) read the status register of nrf module (fifo_status_reg_test())
 *                      9) test and log on UART the success of read and write operations for nrf registers (transmit())
 *                     10) test profiling time of memmove (stdlib) function (lib_memmove_test())
 *                     11) test profiling time of memmove (non-dma) function (my_memmove_test())
 *                     12) test profiling time of memmove (dma) function (dma_memmove_test())
 *                     13) test profiling time of memset (dma) function (dma_memset_test())
 *                     14) test profiling time of memset (non-dma) function (my_memset_test())
 *                     15) test profiling time of memset (stdlib) function (lib_memset_test())
 *
 ***************************************************************************************************/

#include "test.h"

/********************************** profile_test()**********************************************************
 *
 * @name   -  profile_test()
 * @brief  -  function to test profile time for memory functions dma,non-dma,stdlib)
 * @param  -  none
 *
 * long description - This function passes log struct to log buffer.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** profile_test() function definition ***********************************/

void profile_test()
{
	uart_flush("\n\r\n\r");
	uart_flush("Number of bytes  ");
	log_int(10);
	log_int(100);
	log_int(1000);
	log_int(5000);
	uart_flush("\n\r");
	uart_flush("lib-memmove	   ");
	lib_memmove_test(10);
	log_int(t);
	lib_memmove_test(100);
	log_int(t);
	lib_memmove_test(1000);
	log_int(t);
	lib_memmove_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("my-memmove	   ");
	my_memmove_test(10);
	log_int(t);
	my_memmove_test(100);
	log_int(t);
	my_memmove_test(1000);
	log_int(t);
	my_memmove_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("my-memmove-O3  	");
	my_memmove_test_optimized(10);
	log_int(t);
	my_memmove_test_optimized(100);
	log_int(t);
	my_memmove_test_optimized(1000);
	log_int(t);
	my_memmove_test_optimized(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("dma-memmove	   ");
	dma_memmove_test(10);
	log_int(t);
	dma_memmove_test(100);
	log_int(t);
	dma_memmove_test(1000);
	log_int(t);
	dma_memmove_test(5000);
	log_int(t);
	uart_flush("\n\r\n\r");
	uart_flush("Number of bytes  ");
	log_int(10);
	log_int(100);
	log_int(1000);
	log_int(5000);
	uart_flush("\n\r");
	uart_flush("lib-memset	   ");
	lib_memset_test(10);
	log_int(t);
	lib_memset_test(100);
	log_int(t);
	lib_memset_test(1000);
	log_int(t);
	lib_memset_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("my-memset      	 ");
	my_memset_test(10);
	log_int(t);
	my_memset_test(100);
	log_int(t);
	my_memset_test(1000);
	log_int(t);
	my_memset_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("my-memset-O3   	 ");
	my_memset_test_optimized(10);
	log_int(t);
	my_memset_test_optimized(100);
	log_int(t);
	my_memset_test_optimized(1000);
	log_int(t);
	my_memset_test_optimized(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("dma-memset	   ");
	dma_memset_test(10);
	log_int(t);
	dma_memset_test(100);
	log_int(t);
	dma_memset_test(1000);
	log_int(t);
	dma_memset_test(5000);
	log_int(t);
	uart_flush("\n\r\n\r");
	Rxd_Data=0;
}

/********************************** spi_nrf_test()()**********************************************************
 *
 * @name   -  spi_nrf_test()
 * @brief  -  function to test read and write operation to nrf module
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** spi_nrf_test() function definition ***********************************/

void spi_nrf_test()
{
	SPI_init();								//initialize SPI
	tx_addr_test();							//test function for tx_addr register
	rf_setup_test();						//test function for rf_setup register
	rf_ch_reg_test();						//test function for rf_ch register
	config_reg_test();						//test function for config register
	status_reg_test();						//test function for status register
	fifo_status_reg_test();					//test function for fifo_status register
	uart_flush("\n\r\n\r");
	Rxd_Data=0;
}

/********************************** config_reg_test()**********************************************************
 *
 * @name   -  config_reg_test()
 * @brief  -  function to test config read and write operation to nrf module.
 * @param  -  none
 * long description - This function tests config read and write operation to nrf module.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** config_reg_test() function definition ***********************************/

void config_reg_test()
{
	nrf_write_config(0x74);
	uint8_t config;
	config = nrf_read_config();
	delay();
	transmit(CONFIG);
	if(config==0x74){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}

/********************************** tx_addr_test()**********************************************************
 *
 * @name   -  tx_addr_test()
 * @brief  -  function to test read and write operation to nrf module.
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** tx_addr_test() function definition ***********************************/

void tx_addr_test()
{
	uint8_t write[5]={0xAA,0x99,0x88,0x77,0x66};
	nrf_write_TX_ADDR(write);
	uint8_t read[5];
	nrf_read_TX_ADDR(read);
	delay();
	uint8_t i=0;
	uint8_t j=0;
	transmit(TXADDR);
	while(i<5)
	{
		if(*(read+i)==*(write+i))
		{
			j++;
		}
		i++;
	}
	if(j==5){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}


/********************************** rf_setup_test()**********************************************************
 *
 * @name   -  rf_setup_test()
 * @brief  -  function to test read and write operation to nrf module.
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** rf_setup_test() function definition ***********************************/

void rf_setup_test()
{
	nrf_write_rf_setup(0x09);
	uint8_t setup;
	setup = nrf_read_rf_setup();
	delay();
	transmit(RFSETUP);
	if(setup==0x09){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}

/********************************** rf_ch_reg_test()**********************************************************
 *
 * @name   -  rf_ch_reg_test()
 * @brief  -  function to test read and write operation to nrf module
 * @param  -  none
 *
 * long description - This function tests read and write operation to nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** rf_ch_reg_test() function definition ***********************************/

void rf_ch_reg_test()
{
	nrf_write_rf_ch(0x79);
	uint8_t channel;
	channel = nrf_read_rf_ch();
	delay();
	transmit(RFCH);
	if(channel==0x79){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}

/********************************** status_reg_test() **********************************************************
 *
 * @name   -  status_reg_test()
 * @brief  -  function to read the status register of nrf module
 * @param  -  none
 *
 * long description - This function reads the status register of nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** status_reg_test() function definition ***********************************/

void status_reg_test()
{
	uint8_t status = nrf_read_status();
	delay();
	transmit(STATUS);
	uart_flush("SUCCESSFUL");
	SPI_flush();
}

/********************************** fifo_status_reg_test() **********************************************************
 *
 * @name   -  fifo_status_reg_test()
 * @brief  -  function to read the fifo status register of nrf module
 * @param  -  none
 *
 * long description - This function reads the fifo status register of nrf module
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** fifo_status_reg_test() function definition ***********************************/

void fifo_status_reg_test()
{
	uint8_t fifo = nrf_read_fifo_status();
	delay();
	transmit(FIFO);
	uart_flush("SUCCESSFUL");
	SPI_flush();
}

/********************************** transmit()**********************************************************
 *
 * @name   -  transmit()
 * @brief  -  function to test and log on UART the success of read and write operations for nrf registers
 * @param  -  result: result value obtained after operations.
 *
 * long description - This function tests and logs on UART the success of read and write operations for nrf registers
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** transmit() function definition ***********************************/

void transmit(uint8_t result)
{
	uart_flush("\n\r");
	switch (result){
	case CONFIG:
		uart_flush(CON_REG);
		delay();
		break;
	case TXADDR:
		uart_flush(TXADDR_REG);
		delay();
		break;
	case RFSETUP:
		uart_flush(RFSETUP_REG);
		delay();
		break;
	case RFCH:
		uart_flush(RFCH_REG);
		delay();
		break;
	case STATUS:
		uart_flush(STAT_REG);
		delay();
		break;
	case FIFO:
		uart_flush(FIFO_REG);
		delay();
		break;
	}
}

/********************************** lib_memmove_test()**********************************************************
 *
 * @name   -  lib_memmove_test()
 * @brief  -  function to test profiling time of memmove (stdlib) function
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memmove (stdlib) function
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** lib_memmove_test() function definition ***********************************/

void lib_memmove_test(uint32_t len)
{
	uint32_t i=0;
	uint8_t source[len];
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];

	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memmove(source,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

/********************************** my_memmove_test()**********************************************************
 *
 * @name   -  my_memmove_test()
 * @brief  -  function to test profiling time of memmove (non-dma) function
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memmove (non-dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** my_memmove_test() function definition ***********************************/

void my_memmove_test(uint32_t len)
{
	uint32_t i=0;
	uint8_t source[len];
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];

	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	my_memmove(source,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

/********************************** dma_memmove_test()**********************************************************
 *
 * @name   -  dma_memmove_test()
 * @brief  -  function to test profiling time of memmove (dma) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memmove (dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** dma_memmove_test() function definition ***********************************/

void dma_memmove_test(uint32_t len)
{
	uint32_t i=0;
	uint8_t source[len];
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];

	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memmove_dma(source,destination,len,EIGHT_BIT);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

/********************************** dma_memset_test()**********************************************************
 *
 * @name   -  dma_memset_test()
 * @brief  -  function to test profiling time of memset (dma) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memset (dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** dma_memset_test() function definition ***********************************/

void dma_memset_test(uint32_t len)
{
	uint32_t value = 10;
	uint8_t destination[len];
	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memset_dma(value,destination,len,EIGHT_BIT);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

/********************************** my_memset_test()**********************************************************
 *
 * @name   -  my_memset_test()
 * @brief  -  function to test profiling time of memset (non-dma) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memset (non-dma) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** my_memset_test() function definition ***********************************/


void my_memset_test(uint32_t len)
{
	uint32_t value = 10;
	uint8_t destination[len];
	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	my_memset(value,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

/********************************** lib_memset_test()**********************************************************
 *
 * @name   -  lib_memset_test()
 * @brief  -  function to test profiling time of memset (stdlib) function.
 * @param  -  len: length of bytes to be tested
 *
 * long description - This function tests profiling time of memset (stdlib) function.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** lib_memset_test() function definition ***********************************/

void lib_memset_test(uint32_t len)
{
	uint32_t value = 10;
	uint8_t destination[len];
	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memset(destination,value,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

void my_memmove_test_optimized(uint32_t len)
{
	uint32_t i=0;
	uint8_t source[len];
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];

	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	my_memmove_optimized(source,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

void my_memset_test_optimized(uint32_t len)
{
	uint32_t value = 10;
	uint8_t destination[len];
	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	my_memset_optimized(value,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}
