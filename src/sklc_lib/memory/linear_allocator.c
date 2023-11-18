#include <string.h>
#include <stdlib.h>
#include <sklc_lib/memory/linear_allocator.h>

void linear_allocator_create(u64 total_size, void* memory, linear_allocator* out_allocator) {
    if(out_allocator) {
        out_allocator->total = total_size;
        out_allocator->allocated = 0;
        out_allocator->owns_memory = memory == 0 ? true : false;
        if(memory) {
            out_allocator->data = memory;
        } else {
            out_allocator->data = malloc(total_size);
        }
    }    
}

void* linear_allocator_allocate(linear_allocator* allocator, u64 size) {
    if(allocator->allocated + size > allocator->total) return NULL;
    char* data = (char*)allocator->data;
    data += allocator->allocated;
    allocator->allocated += size;
    
    return data;
}

void linear_allocator_destroy(linear_allocator* allocator) {
    if(allocator->owns_memory) free(allocator->data);
    allocator->data = NULL;
    allocator->allocated = 0;
    allocator->total = 0;
}

void linear_allocator_reset(linear_allocator* allocator) {
    memset(allocator->data, 0, allocator->total);
    allocator->allocated = 0;
}