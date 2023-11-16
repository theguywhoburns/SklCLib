#ifndef _SKLC_TESTS_H_
#define _SKLC_TESTS_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/vector.h>

typedef struct test_handler {
    void* internal_handler
} test_handler;

test_handler test_handler_init();
/// @brief Adds the function to the test list, the function must return bool ann accept 0 arguments!
/// @param function_pointer function that takes 0 args and returns bool
void test_handler_add_test(void* function_pointer);
void test_handler_destroy(test_handler* handler);

#endif//_SKLC_TESTS_H_