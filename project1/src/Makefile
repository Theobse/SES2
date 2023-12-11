-include sources.mk

ifeq ($(PLATFORM),HOST)
CC=gcc
C_FLAGS= -Wall -Werror -g -O0 -std=c99 -DPROJECT1
SOURCES=$(HOST_SRCS_C)
INCLUDES=$(INCLUDE_HOST) $(INCLUDE_ARM)

else ifeq ($(PLATFORM),KL25Z) 
CC=arm-none-eabi-gcc 
C_FLAGS= -Wall -Werror -g -O0 -std=c99 \
-mcpu=cortex-m0plus -march=armv6-m -mthumb \
-mfloat-abi=soft -mfpu=fpv4-sp-d16 -specs=nosys.specs -DPROJECT1
SOURCES=$(HOST_SRCS_C) $(KL25Z_SRCS_C) $(KL25Z_SRCS_S)
INCLUDES=$(INCLUDE_HOST) $(INCLUDE_ARM) $(INCLUDE_KL25Z)
LDFLAGS=-T ../platform/MKL25Z128xxx4_flash.ld

else ifeq ($(PLATFORM),BBB)
CC=arm-linux-gnueabihf-gcc 
C_FLAGS=-Wall -Werror -g -O0 -std=c99 -mcpu=cortex-a8 -mthumb -mfloat-abi=hard -DPROJECT1
SOURCES=$(HOST_SRCS_C)
INCLUDES=$(INCLUDE_HOST) $(INCLUDE_ARM)
endif


ifeq ($(PRINT),VERBOSE)
CFLAGS=$(C_FLAGS) -DVERBOSE
else ifeq ($(PRINT),MEMMOVE)
CFLAGS=$(C_FLAGS) -DMEMMOVE
else ifeq ($(PRINT),MEMCOPY)
CFLAGS=$(C_FLAGS) -DMEMCOPY
else ifeq ($(PRINT),MEMSET)
CFLAGS=$(C_FLAGS) -DMEMSET
else ifeq ($(PRINT),MEMREVERSE)
CFLAGS=$(C_FLAGS) -DMEMREVERSE
else
CFLAGS=$(C_FLAGS)
endif


ifeq ($(PLATFORM),KL25Z)
HOST_SRCS_C_O=$(HOST_SRCS_C:.c=.o)
KL25Z_SRCS_C_O=$(KL25Z_SRCS_C:.c=.o)
KL25Z_SRCS_S_O=$(KL25Z_SRCS_S:.S=.o)
HOST_SRCS_C_D=$(HOST_SRCS_C:.c=.d)
KL25Z_SRCS_C_D=$(KL25Z_SRCS_C:.c=.d)
KL25Z_SRCS_S_D=$(KL25Z_SRCS_S:.S=.d)
OBJECTS:= $(HOST_SRCS_C_O) $(KL25Z_SRCS_C_O) $(KL25Z_SRCS_S_O)
DEPENDANCY:= $(HOST_SRCS_C_D) $(KL25Z_SRCS_C_D) $(KL25Z_SRCS_S_D)

else ifeq ($(PLATFORM),BBB)
OBJECTS:= $(SOURCES:.c=.o)
DEPENDANCY:= $(SOURCES:.c=.d)

else ifeq ($(PLATFORM),HOST)
OBJECTS:= $(SOURCES:.c=.o)
DEPENDANCY:= $(SOURCES:.c=.d)
endif

.PHONY: compile-all build clean

#Targets

%.i: %.c	
	-@echo ' '
	-@echo 'preprocessor file .i created: '
	-$(CC) $(CFLAGS) $(INCLUDES) -E -o $@ $< 
	
%.asm: %.c
	-@echo ' '
	-@echo 'assembly file created: '
	-$(CC) $(CFLAGS) $(INCLUDES) -S -o $@ $<
	
%.o: %.c
	-@echo ' '
	-@echo 'object file for .c file created: '
	-$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

%.o: %.S	
	-@echo ' '
	-@echo 'object file for .s file created: '
	-$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
	
%.d: %.c
	-@echo ' '
	-@echo 'dependency file for .c file.. created: '
	-$(CC) $(CFLAGS) $(INCLUDES) -M -o $@ $<

%.d: %.S
	-@echo ' '
	-@echo 'dependency file for .S file.. created: '
	-$(CC) $(CFLAGS) $(INCLUDES) -M -o $@ $<
	
compile-all:$(OBJECTS)

build:$(OBJECTS) $(DEPENDANCY)
	-@echo ' '
	-@echo 'build in process: '
	-$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -Xlinker -Map=project1.map $(OBJECTS) -o project1.elf
	-@echo ' '
	-size project1.elf
	-@echo ' '
	-ls -sh project1.elf

clean:
	-@echo ' '	
	-@echo 'clean all the generated files: '
	-$(RM) *.i *.asm *.o *.d *.out project1.map project1.elf
	-@echo ' '
