#ifndef _SKLC_TESTS_H_
#define _SKLC_TESTS_H_

#include <sklc_lib/defines.h>

typedef struct test_handler {
    void* internal_handler;
} test_handler;

test_handler test_handler_init();
/// @brief Adds the function to the test list, the function must return bool ann accept 0 arguments!
/// @param function_pointer function that takes 0 args and returns bool
void test_handler_add_test(test_handler* handler, void* function_pointer);
bool test_handler_execute_tests(test_handler* handler, bool display_tests_in_console);
void test_handler_destroy(test_handler* handler);

#endif//_SKLC_TESTS_H_