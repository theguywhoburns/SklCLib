#ifndef _SKLC_LIB_MEMORY_LINEAR_ALLOCATOR_H_
#define _SKLC_LIB_MEMORY_LINEAR_ALLOCATOR_H_

#include <sklc_lib/defines.h>

typedef struct linear_allocator {
    void* data;
    u64 allocated;
    u64 total;
    bool owns_memory;
} linear_allocator;

void linear_allocator_create(u64 total_size, void* memory, linear_allocator* out_allocator);

void* linear_allocator_allocate(linear_allocator* allocator, u64 size);

void linear_allocator_destroy(linear_allocator* allocator);

// Resets data of linear allocator without deallocating it
void linear_allocator_reset(linear_allocator* allocator);


#endif//_SKLC_LIB_MEMORY_LINEAR_ALLOCATOR_H_