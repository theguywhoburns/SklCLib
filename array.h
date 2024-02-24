#ifndef _SKLC_DATALANG_ARRAY_H_
#define _SKLC_DATALANG_ARRAY_H_

#include <defines.h>

typedef struct _array {
    void* data;
    u64 stride;
    u64 count;
} array;

array _array_init(u64 count, u64 stride);
void _array_destroy(array* arr);

#define array_init(arr, type, count) {           \
    arr = _array_init(count, sizeof(type));  \
}

#endif//_SKLC_DATALANG_ARRAY_H_