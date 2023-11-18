#include <stdlib.h>
#include <stdio.h>
#include <sklc_lib/vector.h>
#include <sklc_lib/utils/function.h>
#include <sklc_lib/tests/sklc_tests.h>

typedef struct internal_test_handler {
    vector v;
    u64 error_count;
} internal_test_handler;

test_handler test_handler_init() {
    test_handler ret;
    internal_test_handler* t = malloc(sizeof(internal_test_handler));
    t->error_count = 0;
    t->v = vector_create(function);
    ret.internal_handler = t;

    return ret;
}

void test_handler_add_test(test_handler* handler, void* function_pointer) {
    internal_test_handler* itt = handler->internal_handler;
    if(itt == NULL) return;
    function f = {.func_ptr = function_pointer};
    itt->v.push_back(&itt->v, &f);
}

bool test_handler_execute_tests(test_handler* handler, bool display_tests_in_console) {
    internal_test_handler* itt = handler->internal_handler;
    if(itt == NULL) return false;
    u64 func_amount = itt->v.length;
    for(u64 i = 0; i < func_amount; ++i) {
        if(!FUNCTION_CAST(((function*)itt->v.data)[i].func_ptr, bool)()) {
            if(display_tests_in_console) printf("[FAIL]:    Test #%lld\n", i);
            itt->error_count++;
            continue;
        }
        if(display_tests_in_console) printf("[SUCCESS]: Test #%lld\n", i);
    }
    printf("Testing complete...\n Error count: %lld\n", itt->error_count);
    if(itt->error_count > 0) {
        printf("%lld test finished successfully, %lld tests failed\n", func_amount - itt->error_count, itt->error_count);
    }

    return itt->error_count < 0 ? true : false;
}

void test_handler_destroy(test_handler* handler) {
    internal_test_handler* t = handler->internal_handler;
    if(t == NULL) return;
    vector_destroy(&t->v);
    free(t);
    handler->internal_handler = 0;
}