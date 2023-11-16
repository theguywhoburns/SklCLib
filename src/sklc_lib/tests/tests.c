#include <stdlib.h>
#include <sklc_lib/vector.h>
#include <sklc_lib/tests/sklc_tests.h>

typedef bool (*pfn_func)();

// Must be done like that cus bruh
typedef struct function {
    pfn_func func_ptr;
} function;


typedef struct internal_test_handler {
    vector v;
    u64 error_count;
} internal_test_handler;

test_handler test_handler_init() {
    test_handler ret;
    internal_test_handler* t = malloc(sizeof(internal_test_handler));
    t->v = vector_create(function);
    ret.internal_handler = t;
}

void test_handler_destroy(test_handler* handler) {
    internal_test_handler* t = handler->internal_handler;
    vector_destroy(&t->v);
}