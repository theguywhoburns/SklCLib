#include<stdio.h>
#include "DynArray/dynArr.h"

int main(int argc, char **argv) {
    char* test_str = darray_create(char);
    darray_push(test_str, 'H');
    darray_push(test_str, 'e');
    darray_push(test_str, 'l');
    darray_push(test_str, 'l');
    darray_push(test_str, 'o');
    darray_push(test_str, '\0');
    printf("%s", test_str);
    darray_destroy(test_str);
    return 0;
}