/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material.
 *
 *****************************************************************************/
/**
 * @file project1_test.c
 * @brief This file is to be used to project 1.
 *
 * @author Alex Fosdick
 * @date April 2, 2017
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include "platform.h"
#include "project1.h"
#include "memory.h"
#include "conversion.h"
#include "debug.h"


int8_t test_data1() {
  uint8_t * ptr;
  int32_t num = -4096;
  uint32_t digits;
  int32_t value;

  printf("\n\ntest_data1();\n\n");
  ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

  if (! ptr )
  {
    printf("\n\nerror\n");
    return TEST_ERROR;
	
  }

  digits = my_itoa( num, ptr, 16);

  value = my_atoi( ptr, digits, 16);
  #ifdef VERBOSE
  printf("  Initial number: %d\n", num);
  printf("  Final Decimal number: %d\n", value);
  #endif
  free_words( (uint32_t*)ptr );

  if ( value != num )
  {
    return TEST_ERROR;
	printf("\n\n--Error1--");
  }
  return TEST_NO_ERROR;
}

int8_t test_data2() {
  uint8_t * ptr;
  int32_t num = 12345;
  uint32_t digits;
  int32_t value;

  printf("\n\ntest_data2();\n\n");
  ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

  if (! ptr )
  {
    return TEST_ERROR;
  }

  digits = my_itoa( num, ptr, 10);
  value = my_atoi( ptr, digits, 10);
  #ifdef VERBOSE
  printf("  Initial Decimal number: %d\n", num);
  printf("  Final Decimal number: %d\n", value);
  #endif
  free_words( (uint32_t*)ptr );

  if ( value != num )
  {
    return TEST_ERROR;
printf("\n\n--Error2--");
  }
  return TEST_NO_ERROR;
}

int8_t test_memmove1() {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("\n\ntest_memmove1() - NO OVERLAP\n\n");
  set = (uint8_t*) reserve_words( MEM_SET_SIZE_W );

  if (! set )
  {
    return TEST_ERROR;
	printf("\n\n--Error3--");
  }

  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
  {
    set[i] = i;
  }
  
  #ifdef MEMMOVE
  print_memory(set, MEM_SET_SIZE_B);
  printf("\n");
  #endif
  
  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  
  #ifdef MEMMOVE
  print_memory(set, MEM_SET_SIZE_B);
  #endif  

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
    if (set[i + 16] != i)
    {
      ret = TEST_ERROR;
	printf("\n\n--Error3--");
    }
  }

  free_words( (uint32_t*)set );
  return ret;
}

int8_t test_memmove2() {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("\n\ntest_memmove2() -OVERLAP END OF SRC BEGINNING OF DST\n\n");
  set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

  if (! set )
  {
    return TEST_ERROR;
	printf("\n\n--Error4--");
  }
  ptra = &set[0];
  ptrb = &set[8];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++) {
    set[i] = i;
  }
  
  #ifdef MEMMOVE
  print_memory(set, MEM_SET_SIZE_B);
  printf("\n");
  #endif
  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  #ifdef MEMMOVE
  print_memory(set, MEM_SET_SIZE_B);
  #endif
  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
    if (set[i + 8] != i)
    {
      ret = TEST_ERROR;
	printf("\n\n--Error4--");
    }
  }

  free_words( (uint32_t*)set );
  return ret;
}

int8_t test_memmove3() {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("\n\ntest_memove3() - OVERLAP END OF DEST BEGINNING OF SRC\n\n");
  set = (uint8_t*)reserve_words( MEM_SET_SIZE_W);

  if (! set )
  {
    return TEST_ERROR;
	printf("\n\n--Error5--");
  }
  ptra = &set[8];
  ptrb = &set[0];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
  {
    set[i] = i;
  }

  #ifdef MEMMOVE
  print_memory(set, MEM_SET_SIZE_B);
  printf("\n");
  #endif
  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  #ifdef MEMMOVE
  print_memory(set, MEM_SET_SIZE_B);
  #endif

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
    if (set[i] != (i + 8))
    {
      ret = TEST_ERROR;
	printf("\n\n--Error5--");
    }
  }


  free_words( (uint32_t*)set );
  return ret;

}

int8_t test_memcpy() {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("\n\ntest_memcpy()\n\n");
  set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

  if (! set )
  {
    return TEST_ERROR;
	printf("\n\n--Error6--");
  }
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++) {
    set[i] = i;
  }

  #ifdef MEMCOPY
  print_memory(set, MEM_SET_SIZE_B);
  printf("\n");
  #endif 
  my_memcpy(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  #ifdef MEMCOPY
  print_memory(set, MEM_SET_SIZE_B);
  #endif

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
    if (set[i+16] != i)
    {
      ret = TEST_ERROR;
	printf("\n\n--Error6--");
    }
  }

  free_words( (uint32_t*)set );
  return ret;
}

int8_t test_memset()
{
  uint8_t i;
  uint8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("\n\ntest_memset()\n\n");
  set = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (! set )
  {
    return TEST_ERROR;
	printf("\n\n--Error7--");
  }
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
  {
    set[i] = i;
  }
  
  #ifdef MEMSET
  print_memory(set, MEM_SET_SIZE_B);
  printf("\n");
  #endif
  my_memset(ptra, MEM_SET_SIZE_B, 0xFF);
  #ifdef MEMSET
  print_memory(set, MEM_SET_SIZE_B);
  printf("\n");
  #endif
  my_memzero(ptrb, MEM_ZERO_LENGTH);
  #ifdef MEMSET
  print_memory(set, MEM_SET_SIZE_B);
  #endif

  /* Validate Set & Zero Functionality */
  for (i = 0; i < MEM_ZERO_LENGTH; i++)
  {
    if (set[i] != 0xFF)
    {
      ret = TEST_ERROR;
	printf("\n\n--Error7--");
    }
    if (set[16 + i] != 0)
    {
      ret = TEST_ERROR;
	printf("\n\n--Error7--");
    }
  }

  free_words( (uint32_t*)set );
  return ret;
}

int8_t test_reverse()
{
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * copy;
  uint8_t set[MEM_SET_SIZE_B] = {0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26,
                                 0x48, 0x63, 0x20, 0x66, 0x6F, 0x00, 0x20, 0x33,
                                 0x72, 0x75, 0x74, 0x78, 0x21, 0x4D, 0x20, 0x40,
                                 0x20, 0x24, 0x7C, 0x20, 0x24, 0x69, 0x68, 0x54
                               };

  printf("\n\ntest_reverse()\n\n");
  copy = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (! copy )
  {
    return TEST_ERROR;
	printf("\n\n--Error8--");
  }

  my_memmove(set, copy, MEM_SET_SIZE_B);
  #ifdef MEMREVERSE
  print_memory(copy, MEM_SET_SIZE_B);
  printf("\n");
  print_memory(set, MEM_SET_SIZE_B);
  printf("\n");
  #endif
  my_reverse(set, MEM_SET_SIZE_B);
  #ifdef MEMREVERSE
  print_memory(set, MEM_SET_SIZE_B);
  #endif

  for (i = 0; i < MEM_SET_SIZE_B; i++)
  {
    if (set[i] != copy[MEM_SET_SIZE_B - i - 1])
    {
      ret = TEST_ERROR;
	printf("\n\n--Error8--");
    }
  }

  free_words( (uint32_t*)copy );
  return ret;
}

void project1(void)
{
  uint8_t i;
  int8_t failed = 0;
  int8_t results[TESTCOUNT];

  results[0] = test_data1();
  results[1] = test_data2();
  results[2] = test_memmove1();
  results[3] = test_memmove2();
  results[4] = test_memmove3();
  results[5] = test_memcpy();
  results[6] = test_memset();
  results[7] = test_reverse();

  for ( i = 0; i < TESTCOUNT; i++)
  {
    failed += results[i];
  }

  printf("\n****************************************\n");
  printf("\nTest Results:\n");
  printf(" \n PASSED: %d / %d\n", (TESTCOUNT - failed), TESTCOUNT);
  printf(" \n FAILED: %d / %d\n", failed, TESTCOUNT);
  printf("\n****************************************\n");
}
