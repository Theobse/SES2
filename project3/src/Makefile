-include sources.mk


ifeq ($(PLATFORM),HOST)
CC=gcc
CFLAGS= -Wall -g -O0 -std=c99 -DPROJECT3_1
SOURCES=$(HOST_SRCS_C)
INCLUDES=$(INCLUDE_HOST)

else ifeq ($(PLATFORM),KL25Z) 
CC=arm-none-eabi-gcc 
CFLAGS= -Wall -g -O0 -std=c99 \
-mcpu=cortex-m0plus -march=armv6-m -mthumb \
-mfloat-abi=soft -mfpu=fpv4-sp-d16 -specs=nosys.specs -DPROJECT3
SOURCES=$(KL25Z_SRCS_C) $(KL25Z_SRCS_S)
INCLUDES=$(INCLUDE_HOST) $(INCLUDE_ARM) $(INCLUDE_KL25Z)
LDFLAGS=-T ../platform/MKL25Z128xxx4_flash.ld

else ifeq ($(PLATFORM),BBB)
CC=arm-linux-gnueabihf-gcc 
CFLAGS=-Wall -g -O0 -std=c99 -mcpu=cortex-a8 -mthumb -mfloat-abi=hard -DPROJECT3_1
SOURCES=$(HOST_SRCS_C)
INCLUDES=$(INCLUDE_HOST) $(INCLUDE_ARM)

endif


ifeq ($(PLATFORM),KL25Z)
OBJECTS:= $(HOST_SRCS_C:.c=.o) $(KL25Z_SRCS_C:.c=.o) $(KL25Z_SRCS_S:.S=.o)
DEPENDANCY:= $(HOST_SRCS_C:.c=.d) $(KL25Z_SRCS_C:.c=.d) $(KL25Z_SRCS_S:.S=.d)

else ifeq ($(PLATFORM),BBB)
OBJECTS:= $(SOURCES:.c=.o)
DEPENDANCY:= $(SOURCES:.c=.d)

else ifeq ($(PLATFORM),HOST)
OBJECTS:= $(SOURCES:.c=.o)
DEPENDANCY:= $(SOURCES:.c=.d)

endif


.PHONY: compile-all build exit

# Targets

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

# compile but not link
	
compile-all:$(OBJECTS)


# compile and link

build:$(OBJECTS) $(DEPENDANCY)
	-@echo ' '
	-@echo 'build in process: '
	-$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -Xlinker -Map=project3.map $(OBJECTS) -o project3.elf
	-@echo ' '
	-size project3.elf
	-@echo ' '
	-ls -sh project3.elf

# library for unit test

TEST_SRCS = \
	memory.c \
	conversion.c \
	circbuf.c \
	test_memory.c \
	test_conversion.c \
	test_circbuf.c 

TEST_OBJS = $(TEST_SRCS:%.c=%.o)

TEST_HEADERS = $(TEST_SRCS:%.c=%.h)

LIB = libutils.a


# test
MAIN_SRCS = \
	test.c

MAIN_OBJS = $(MAIN_SRCS:%.c=%.o)

MAIN_EXE = test.out


.PHONY : test clean

# build and run cmocka test

test : $(MAIN_EXE)
	./$(MAIN_EXE)

$(LIB) : $(TEST_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(MAIN_EXE) : $(MAIN_SRCS) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lcmocka

# delete created files

clean : 
	-@echo ' '	
	-@echo 'clean all the generated files: '	
	-rm -rf *~ *.o $(LIB) $(EXE) $(MAIN_EXE) *.dSYM/	
	-$(RM) *.i *.asm *.o *.d *.out project3.map project3.elf
	-@echo ' '



#########################################################################


