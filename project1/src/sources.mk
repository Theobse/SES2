
# Add Source files to build variables

HOST_SRCS_C = ./main.c ./project1.c ./conversion.c ./memory.c ./debug.c

KL25Z_SRCS_C = ./system_MKL25Z4.c

KL25Z_SRCS_S = ./startup_MKL25Z4.S



# Define Platform specific include files 

INCLUDE_HOST= -I ../include/common

INCLUDE_ARM= -I ../include/CMSIS

INCLUDE_KL25Z= -I ../include/kl25z
