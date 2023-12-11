#include "test_conversion.h"


void test_big_to_little1()
{
   uint32_t *data = NULL;
   uint32_t *ret;   

   ret=big_to_little32(data, 1);

   assert_ptr_equal(ret,NULL);
}

void test_big_to_little2()
{
   uint32_t a=0x12345678;
   uint32_t *data = &a;
   uint32_t *ret;   

   ret=big_to_little32(data, 1);

   assert_int_equal(*ret,0x78563412);
}


void test_little_to_big1()
{
   uint32_t *data = NULL;
   uint32_t *ret;   

   ret=little_to_big32(data, 1);

   assert_ptr_equal(ret,NULL);
}

void test_little_to_big2()
{
   uint32_t a=0x12345678;
   uint32_t *data = &a;
   uint32_t *ret;   

   ret=little_to_big32(data, 1);

   assert_int_equal(*ret,0x78563412);
}


   
