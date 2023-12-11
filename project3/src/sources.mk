
# Add Source files to build variables

HOST_SRCS_C = ./main.c ./project3_1.c ./memory.c

KL25Z_SRCS_C =./main.c ./project3.c ./circbuf.c ./conversion.c ./dma.c ./gpio.c ./logbuf.c ./logger.c ./memory.c ./nordic.c ./profiler.c ./rtc.c ./spi.c ./test.c ./uart.c ./system_MKL25Z4.c

KL25Z_SRCS_S = ./startup_MKL25Z4.S



# Define Platform specific include files 

INCLUDE_HOST= -I ../include/common

INCLUDE_ARM= -I ../include/CMSIS

INCLUDE_KL25Z= -I ../include/kl25z
