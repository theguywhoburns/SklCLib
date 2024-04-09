#ifndef _SKLC_UTILS_CHUNKVEC_H_
#define _SKLC_UTILS_CHUNKVEC_H_
#include <sklc_lib/utils/vector.h>

typedef struct ChVec ChVec;
typedef struct ChVecInternal ChVecInternal;
/// @warning THERE IS NO INSERT OR REMOVE FUNCTIONS DUE 1THE INNER WORKINGS OF CHVEC
struct ChVec {
    vector chunk_vector; //This shit keeps track of chunks, will reimplement for more perfomance later
    ChVecInternal* internal;

    u64  (*Stride) (ChVec* this);
    u64  (*ChStride)(ChVec* this);   //Capacity of one chunk in bytes
    u64  (*TotalCap)(ChVec* this);//Total capacity

    void (*push)(ChVec* this, void* val);
    void*(*pop )(ChVec* this);
    //Will allocate a new instance of a pointer
    //Example int a = 10;
    //will allocate a new int in the vector
    //So if you use smth like string <- Use set_no_alloc with string_copy, or copy the instance with all the pointers yourself
    //Same with at, use __at_no_alloc for this type of shit
    void*(*at)(ChVec* this, u64 index);
    //Will allocate a new instance of a pointer
    //Example int a = 10;
    //will allocate a new int in the vector
    //So if you use smth like string <- Use set_no_alloc with string_copy, or copy the instance with all the pointers yourself
    //Same with at, use __at_no_alloc for this type of shit
    void (*set)(ChVec* this, void* value, u64 index);
    void (*set_no_alloc)(ChVec* this, void* value, u64 index);
    void (*shrink)(ChVec* this);
    void (*reserve)(ChVec* this, u32 amount_of_chunks);

    //FOR USE IN IF STATEMENTS
    void*(*__at_no_alloc)(ChVec* this, u64 index);

};

ChVec ChVec_Create  (u32 max_element_size, u32 max_elements_in_chunk);
ChVec ChVec_CreateEx(u32 max_element_size, u32 max_elements_in_chunk, u32 num_prealloc_chunks);

#endif//_SKLC_UTILS_CHUNKVEC_H_