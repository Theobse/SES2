#include "test_circbuf.h"

void test_allocate_free()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    CB_init(buff,buff_length);
    
    assert_ptr_not_equal(buff->buffer,NULL);
    assert_int_equal(buff->length,buff_length);
    
    CB_destroy(buff);
}

void invalid_pointer()
{
    CB_t *buff=NULL;
    
    uint8_t buff_length = 10;
    uint8_t ret;

    ret=CB_init(buff,buff_length);

    assert_int_equal(ret,NULL_ERROR);
}

void non_init_buffer()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    CB_init(buff,buff_length);


    assert_ptr_not_equal(buff->buffer,NULL);
    assert_int_equal(buff->length,buff_length);
    assert_ptr_equal(buff->buffer,buff->head);
    assert_ptr_equal(buff->buffer,buff->tail);
    assert_int_equal(buff->count,0);

    CB_destroy(buff);
}
    

void add_remove()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    
    CB_init(buff,buff_length);
    
    if(buff->length==buff_length)
	assert_ptr_not_equal(buff->buffer,NULL);
    
    uint8_t add = 15;
    uint8_t remove = 0;
    
    CB_buffer_add_item(buff,&add);
    CB_buffer_remove_item(buff,&remove);

    assert_int_equal(remove,add);

    CB_destroy(buff);
}


void buffer_full()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    
    CB_init(buff,buff_length);
    
    if(buff->length==buff_length)
	assert_ptr_not_equal(buff->buffer,NULL);
    
    uint8_t i;
    uint8_t ret;

    ret=CB_is_full(buff);
    assert_int_equal(ret,BUFFER_NOT_FULL);
   
    for(i=0;i<buff_length;i++)
    {
   	CB_buffer_add_item(buff,&i);
    }

    ret=CB_is_full(buff);
    assert_int_equal(ret,BUFFER_FULL);
   
    CB_destroy(buff);
}
    

void buffer_empty()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    
    CB_init(buff,buff_length);
    
    if(buff->length==buff_length)
	assert_ptr_not_equal(buff->buffer,NULL);
    
    uint8_t i;
    uint8_t ret;

    ret=CB_is_empty(buff);
    assert_int_equal(ret,BUFFER_EMPTY);

    for(i=0;i<buff_length;i++)
    {
   	CB_buffer_add_item(buff,&i);
    }

    ret=CB_is_empty(buff);
    assert_int_equal(ret,BUFFER_NOT_EMPTY);

    CB_destroy(buff);
}


void wrap_add()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    
    CB_init(buff,buff_length);
    
    if(buff->length==buff_length)
	assert_ptr_not_equal(buff->buffer,NULL);
    
    uint8_t i;
    uint8_t add=12;
    uint8_t remove;
    uint8_t ret;

    for(i=0;i<buff_length;i++)
    {
   	CB_buffer_add_item(buff,&i);
    }

    ret=CB_is_full(buff);
    assert_int_equal(ret,BUFFER_FULL);

    CB_buffer_remove_item(buff,&remove);

    CB_buffer_add_item(buff,&add);
    assert_int_equal(*buff->buffer,add);

    CB_destroy(buff);
}  
  

void wrap_remove()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    
    CB_init(buff,buff_length);
    
    if(buff->length==buff_length)
	assert_ptr_not_equal(buff->buffer,NULL);
    
    uint8_t i;
    uint8_t add=12;
    uint8_t remove;
    uint8_t ret;

    for(i=0;i<buff_length;i++)
    {
   	CB_buffer_add_item(buff,&i);
    }

    ret=CB_is_full(buff);
    assert_int_equal(ret,BUFFER_FULL);

    CB_buffer_remove_item(buff,&remove);

    CB_buffer_add_item(buff,&add);
    assert_int_equal(*buff->buffer,add);
    
    for(i=0;i<buff_length;i++)
    {
   	CB_buffer_remove_item(buff,&remove);
    }

    assert_ptr_equal(buff->tail,buff->buffer);

    CB_destroy(buff);
} 


void overfill()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    
    CB_init(buff,buff_length);
    
    if(buff->length==buff_length)
	assert_ptr_not_equal(buff->buffer,NULL);
    
    uint8_t i;
    uint8_t add=12;
    uint8_t ret;

    for(i=0;i<buff_length;i++)
    {
   	CB_buffer_add_item(buff,&i);
    }
     
    ret=CB_is_full(buff);
    assert_int_equal(ret,BUFFER_FULL);

    ret=CB_buffer_add_item(buff,&add);
    assert_int_equal(ret,BUFFER_FULL);

    CB_destroy(buff);
}


void overempty()
{
    CB_t b;
    CB_t *buff=&b;
    
    uint8_t buff_length = 10;
    
    CB_init(buff,buff_length);
    
    if(buff->length==buff_length)
	assert_ptr_not_equal(buff->buffer,NULL);

    uint8_t remove;
    uint8_t ret;

    ret=CB_buffer_remove_item(buff,&remove);
    assert_int_equal(ret,BUFFER_EMPTY);

    CB_destroy(buff);
}

    
