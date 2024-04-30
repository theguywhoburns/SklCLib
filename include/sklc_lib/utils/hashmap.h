#ifndef _SKLC_LIB_HASHMAP_H_
#define _SKLC_LIB_HASHMAP_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/vector.h>

// +- 24 bytes
typedef struct KeyValPair {
    void* key;
    void* val;
    uint32_t keysize; //SIZE OF A KEY VARIABLE, THA REAL SIZE MAY BE DIFFERENT
    uint32_t valsize; //SIZE OF A VALUE VARIABLE, THA REAL SIZE MAY BE DIFFERENT
} KeyValPair;

typedef struct hashmap hashmap;
/// @brief Hash function declaration
/// @param map map struct pointer
/// @param data key pointer that will be stored in kvp
/// @param datasize size of that data :|
/// @param length length of the hash array
/// @param seed0 no need to describe
/// @param seed1 no need to describe
/// @returns The array index where the KeyValuePair will be put to
typedef uint64_t (*pfnhash)(hashmap* map, const void* data, uint64_t datasize, uint64_t length, uint64_t seed0, uint64_t seed1);
/// The resulting void* will be put in val variable in KeyValPair
/// Example: value is int, int* ret = malloc(valsize);  *ret = *(int*)pval; return ret;
/// Example: value is string, string* ret = malloc(valsize); StringDuplicate(*(string*)pval); return ret; 
typedef void* (*pfnalloc)(void* pval, uint64_t valsize);
/// pval is a pointer to a value that needs to be freed
/// Example: value is int, free(pval)
/// Example: value is string, StringDestroy(pval); free(pval);
typedef void  (*pfnfree) (void* pval);

struct hashmap {
    pfnhash  hashfunc;
    pfnalloc allocfunc;
    pfnfree  freefunc;
    void* KeyValPairArr;
};

uint64_t SIP64(const uint8_t *in, const size_t inlen, uint64_t seed0, uint64_t seed1);

//Default hash function, use for functions with known size like int float cstring, structs with no pointers, etc, dont use with things like normal strings or structs with pointers, for this write custom hashfunc
inline uint64_t default_hashfunc(const void* data, uint64_t datasize, uint64_t length, uint64_t seed0, uint64_t seed1) {
    return SIP64((const uint8_t*)data, (size_t)datasize, seed0, seed1) % length;
}



#endif//_SKLC_LIB_HASHMAP_H_