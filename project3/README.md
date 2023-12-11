This project involves writing a binary logger application for a microcontroller that uses the prior work with the UART and Circular Buffers. A logger enables one to report data to a PC, this helps to interpret what is happening with the embedded system. This application is extended to use DMA as a mechanism to off-load transmitting of the data. The execution time of various operations is documented using a profiler and the systick counter. In the last part of this project, this code is leveraged to communicate with the Nordic Wireless transceiver via the Serial Peripheral Interface (SPI).

The objectives of this project are:
    1) Use DMA to perform data memory movements.
    2) Enhance the circular buffer code to be more efficient and robust.
    3) Develop a binary ogger o end ata o  UART.
    4) Profile the library functions to determine execution time.
    5) Create a SPI driver to interface with a Nordic Wireless transceiver.


Profiling Test Results:
1) Profiling time for memove functions for 1 byte data (Time in micro seconds)

	           	  10 bytes    100 bytes   1000 bytes   5000 bytes
		   lib-memmove	      3            20	      188	  170
		   my-memmove	      7            55	       31	  150
		   my-memmove-O3     2             6	       48	  236
		   dma-memmove	      8            12          50	  216

2) Profiling time for memset functions for 1 byte data (Time in micro seconds)

	           	  10 bytes    100 bytes   1000 bytes   5000 bytes
		    lib-memset	      2	            15	      146	  218
		    my-memset	      6	            47	      203	  245
		    my-memset-O3     2	            15	      147	  218
		    dma-memset	      8	            12	       49	  216
