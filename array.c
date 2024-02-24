#include <stdlib.h>
#include <util/array.h>

array _array_init(u64 count, u64 stride) {
    return (array){.count = count, .stride = stride, .data = malloc(stride * count)};
}

void _array_destroy(array* arr) {
    arr->count = 0;    
    arr->stride= 0;    
    free(arr->data);
}