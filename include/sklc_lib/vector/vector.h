#ifndef _SKLC_LIB_VECTOR_H_
#define _SKLC_LIB_VECTOR_H_


// Used by the defines, DONT'USE IT BY YOURSELF
typedef struct _vector { 

    // WARNING: DO NOT MANUALLY CHANGE ANYTHING BELOW!!!
    void* data;                 // Vector's data

    unsigned long long stride;  // Size of the element
    unsigned long long length;  // Number of elements currently used
    unsigned long long capacity;// How much items can it hold before reallocating;

    void (*push_back)(struct _vector* vec, const void* data);
    void* (*pop_back)(struct _vector* vec);

    void (*set_at)(struct _vector* vec, unsigned long long index, void* val);
    void*(*get_at)(struct _vector* vec, unsigned long long index);

    void (*insert_at)(struct _vector* vec, const void* data, unsigned long long index);
    void*(*remove_at)(struct _vector* vec, unsigned long long index);

    void (*clear)(struct _vector* vec);

    void (*resize)(struct _vector* vec);

    // adds passed length to the current capacity
    void (*reserve)(struct _vector* vec, unsigned long long capacity);

} _vector;

#define vector _vector

vector _vector_create(unsigned long long capacity, unsigned long long stride);
void vector_destroy(vector* vec);

#define vector_create(type) _vector_create(1, sizeof(type))

#endif//_SKLC_LIB_VECTOR_H_