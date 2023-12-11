#include "test_memory.h"

void test_memmove1()
{
   uint8_t * ret;
   uint8_t * ptra=NULL;
   uint8_t * ptrb=NULL;
   
   ret=my_memmove(ptra, ptrb, 15);	
   
   assert_ptr_equal(ret,NULL);
}


void test_memmove2()
{
   uint8_t i;
   uint8_t * set;
   uint8_t * ptra;
   uint8_t * ptrb;
   set = (uint8_t*) malloc(32*sizeof(uint8_t));
   
   ptra = &set[0];
   ptrb = &set[16];
   
   for( i = 0; i < 32; i++) 
   {
    	set[i] = i;
   }
   
   my_memmove(ptra, ptrb, 16);	
  
   for (i = 0; i < 16; i++)
   {
        assert_int_equal(*(ptrb+i),*(ptra+i));

   }

}


void test_memmove3()
{
   uint8_t i;
   uint8_t * set;
   uint8_t * ptra;
   uint8_t * ptrb;
   set = (uint8_t*) malloc(32*sizeof(uint8_t));
   
   ptra = &set[8];
   ptrb = &set[0];
   
   for( i = 0; i < 32; i++) 
   {
    	set[i] = i;
   }
   
   my_memmove(ptra, ptrb, 16);	

   for (i = 0; i < 16; i++)
   {
        assert_int_equal(*(set+i),(i+8));
   }
}


void test_memmove4()
{
   uint8_t i;
   uint8_t * set;
   uint8_t * ptra;
   uint8_t * ptrb;
   set = (uint8_t*) malloc(32*sizeof(uint8_t));
   
   ptra = &set[0];
   ptrb = &set[8];
   
   for( i = 0; i < 32; i++) 
   {
    	set[i] = i;
   }
   
   my_memmove(ptra, ptrb, 16);	

   for (i = 0; i < 16; i++)
   {
   	assert_int_equal(*(set+i+8),i);

   }
   
}

void test_memset1()
{
   uint8_t *set=NULL;
   uint8_t *ret;
   
   ret=my_memset(set,5,3);
   
   assert_ptr_equal(ret,NULL);

}

void test_memset2()
{
   uint8_t i;
   uint8_t *set;

   set = (uint8_t*) malloc(40*sizeof(uint8_t));
   
   my_memset(set,5,3);
   for(i=0;i<5;i++)
   {
    	assert_int_equal(*(set+i),3);
   }
}

void test_memzero1()
{
   uint8_t *set=NULL;
   uint8_t *ret;
   
   ret=my_memzero(set,5);
   
   assert_ptr_equal(ret,NULL);

}

void test_memzero2()
{
   uint8_t i;
   uint8_t *set;

   set = (uint8_t*) malloc(40*sizeof(uint8_t));
   
   my_memzero(set,5);
   for(i=0;i<5;i++)
   {
    	assert_int_equal(*(set+i),0);
   }
}

void test_memreverse1()
{
   //uint8_t i;
   //uint8_t set[8] = {0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26};
   uint8_t *rev = NULL;
   uint8_t *ret;
   
   ret=my_reverse(rev,8);
   
   assert_ptr_equal(ret,NULL);
}

void test_memreverse2()
{
   uint8_t i;
   uint8_t set[7] = {0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72};
   uint8_t temp[7];
   for(i=0;i<7;i++)
   {
 	temp[i]=set[i];
   }
   
   uint8_t *rev = set;
   uint8_t *ret;
   
   ret=my_reverse(rev,7);
   
   for(i=0;i<7;i++)
   {
   	assert_int_equal(*(ret+i),temp[6-i]);
   }
}

void test_memreverse3()
{
   uint8_t i;
   uint8_t set[8] = {0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26};
   uint8_t temp[8];
   for(i=0;i<8;i++)
   {
 	temp[i]=set[i];
   }
   
   uint8_t *rev = set;
   uint8_t *ret;
   
   ret=my_reverse(rev,8);
   
   for(i=0;i<8;i++)
   {
   	assert_int_equal(*(ret+i),temp[7-i]);
   }
}

void test_memreverse4()
{
   uint8_t i;
   uint8_t set[255];
   uint8_t temp[255];
   for(i=0;i<255;i++)
   {
 	temp[i]=i+1;
  	set[i]=i+1;
   }
   
   uint8_t *rev = set;
   uint8_t *ret;
   
   ret=my_reverse(rev,255);
   
   for(i=0;i<255;i++)
   {
   	assert_int_equal(*(ret+i),temp[254-i]);
   }
}


