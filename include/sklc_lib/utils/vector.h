#ifndef _SKLC_LIB_VECTOR_H_
#define _SKLC_LIB_VECTOR_H_

#include <sklc_lib/defines.h>

// Used by the defines, DONT'USE IT BY YOURSELF
typedef struct _vector { 

    void* data;                 // Vector's data

    // WARNING: DO NOT MANUALLY CHANGE ANYTHING BELOW!!!
    uint64_t stride;  // Size of the element
    uint64_t length;  // Number of elements currently used
    uint64_t capacity;// How much items can it hold before reallocating;
    uint64_t amount_of_elements_to_add_when_resizing;

    void (*push_back)(struct _vector* vec, const void* data);
    void* (*pop_back)(struct _vector* vec);

    void (*set_at)(struct _vector* vec, uint64_t index, void* val);
    void*(*get_at)(struct _vector* vec, uint64_t index);

    void (*insert_at)(struct _vector* vec, const void* data, uint64_t index);
    void*(*remove_at)(struct _vector* vec, uint64_t index);

    void (*clear)(struct _vector* vec);

    void (*resize)(struct _vector* vec);

    // adds passed length to the current capacity
    
    void (*reserve)(struct _vector* vec, uint64_t capacity);

    bool is_struct_ptr;
    
} _vector;

#define vector _vector

vector _vector_create(uint64_t capacity, uint64_t stride);

// Use thes ONLY when you want to create an allocated vector or an array of vectors
vector* _vector_create_ptr(uint64_t capacity, uint64_t stride);
void vector_destroy(vector* vec);

#define vector_create(type) _vector_create(1, sizeof(type))
#define vector_create_ptr(type) _vector_create_ptr(1, sizeof(type))

#endif//_SKLC_LIB_VECTOR_H_