#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "circbuf.h"


void test_allocate_free();
void invalid_pointer();
void non_init_buffer();
void add_remove();
void buffer_full();
void buffer_empty();
void wrap_add();
void wrap_remove();
void overfill();
void overempty();



