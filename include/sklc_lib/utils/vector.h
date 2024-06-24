#ifndef _SKLC_LIB_VECTOR_H_
#define _SKLC_LIB_VECTOR_H_

#include <sklc_lib/defines.h>

// Used by the defines, DONT'USE IT BY YOURSELF
struct _vector { 

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
    
    int  (*compare)(struct _vector* a, struct _vector* b);

    struct _vector (*copy)(struct _vector* vec);

    // adds passed length to the current capacity
    void (*reserve)(struct _vector* vec, uint64_t capacity);

    bool is_struct_ptr;

    void (*value_destructor)(struct _vector* vec, void* value);
    void*(*value_copy)(struct _vector* vec, void* value);
    int  (*_compare)(struct _vector* vec, void* a, void* b);
};

#define vector struct _vector

vector _vector_create(uint64_t capacity, uint64_t stride, 
    void (*val_dtor)(vector* vec, void* val), 
    void*(*val_cpy)(vector* vec, void* val),
    int  (*cmp)(vector* vec, void* a, void* b));

// Use thes ONLY when you want to create an allocated vector or an array of vectors
vector* _vector_create_ptr(uint64_t capacity, uint64_t stride,
    void (*val_dtor)(vector* vec, void* val), 
    void*(*val_cpy)(vector* vec, void* val),
    int  (*cmp)(vector* vec, void* a, void* b));
void vector_destroy(vector* vec);

#define vector_create(type) _vector_create(1, sizeof(type), __vector_def_val_dtor, __vector_def_val_cpy, __vector_def_cmp)
#define vector_create_ptr(type) _vector_create_ptr(1, sizeof(type), __vector_def_val_dtor, __vector_def_val_cpy, __vector_def_cmp)

// Default functions
void __vector_def_val_dtor(vector* vec, void* val);
void*__vector_def_val_cpy (vector* vec, void* val);
int  __vector_def_cmp     (vector* vec, void* a, void* b);

void __vector_def_string_dtor(vector* vec, void* val);
void*__vector_def_string_cpy(vector* vec, void* val);
int  __vector_def_string_cmp(vector* vec, void* a, void* b);

#endif//_SKLC_LIB_VECTOR_H_