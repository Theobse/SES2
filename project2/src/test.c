/***************************************************************************************************
 *
 * @author Preshit Harlikar, Shivam Khandelwal
 * @file test.c
 * @brief This file includes cmocka test functions
 * @date October 24, 2017
 *
 * long description - The uart.c file includes functions to -
 *                      1) test memory.c
 *                      2) test conversion.c
 *                      3) test cirbuf.c
 ***************************************************************************************************/


#include "test_memory.h"
#include "test_circbuf.h"
#include "test_conversion.h"


int main()
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_memmove1),
    cmocka_unit_test(test_memmove2),
    cmocka_unit_test(test_memmove3),
    cmocka_unit_test(test_memmove4),
    cmocka_unit_test(test_memset1),
    cmocka_unit_test(test_memset2),
    cmocka_unit_test(test_memzero1),
    cmocka_unit_test(test_memzero2),
    cmocka_unit_test(test_memreverse1),
    cmocka_unit_test(test_memreverse2),
    cmocka_unit_test(test_memreverse3),
    cmocka_unit_test(test_memreverse4),
    cmocka_unit_test(test_allocate_free),
    cmocka_unit_test(invalid_pointer),
    cmocka_unit_test(non_init_buffer),
    cmocka_unit_test(add_remove),
    cmocka_unit_test(buffer_full),
    cmocka_unit_test(buffer_empty),
    cmocka_unit_test(wrap_add),
    cmocka_unit_test(wrap_remove),
    cmocka_unit_test(overfill),
    cmocka_unit_test(overempty),
    cmocka_unit_test(test_big_to_little1),
    cmocka_unit_test(test_big_to_little2),
    cmocka_unit_test(test_little_to_big1),
    cmocka_unit_test(test_little_to_big2),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}     
