#ifndef _SKLC_LIB_HASHMAP_H_
#define _SKLC_LIB_HASHMAP_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/string.h>

// 16 bytes
typedef struct KeyValPair {
    void* key;
    void* val;
} KeyValPair;

typedef struct hashmap hashmap;

/// @brief Hash function declaration
/// @param map map struct pointer
/// @param data key pointer that will be stored in kvp
/// @param length length of the hash array
/// @param seed0 no need to describe
/// @param seed1 no need to describe
/// @returns The array index where the KeyValuePair will be put to
typedef uint64_t (*pfnhash)(hashmap* map, const void* data, uint64_t length, uint64_t seed0, uint64_t seed1);
/// The resulting void* will be put in val variable in KeyValPair
/// Example: value is int, int* ret = malloc(sizeof(int));  *ret = *(int*)pval; return ret;
/// Example: value is string, string* ret = malloc(sizeof(string)); StringDuplicate(*(string*)pval); return ret; 
typedef void* (*pfncopy)(void* pval);
/// pval is a pointer to a value that needs to be freed
/// Example: value is int, free(pval)
/// Example: value is string, StringDestroy(pval); free(pval);
typedef void  (*pfndestroy) (void* pval);

typedef int (*pfncompare)(
    const void* a, 
    const void* b
);

struct hashmap {
    pfnhash     hashfunc;
    pfncopy     copykeyfunc;
    pfncopy     copyfunc;
    pfndestroy  destroykeyfunc;
    pfndestroy  destroyfunc;
    pfncompare  keycomparefunc;
    pfncompare  comparefunc;
    vector      KeyValPairVec;

    // Iterates in the hashmap like in a for loop
    // Expected to be used with closures, also DO NOT DEALLOCATE THE VARIABLES YOURSELVES
    void (*iterate)(hashmap* map, void (*fn)(void* key, void* val, void* ctx), void* ctx);
    bool (*exists) (hashmap* map, void* key);
    void*(*get)    (hashmap* map, void* key, bool copy);
    void (*set)    (hashmap* map, void* key, void* val);
    void (*remove) (hashmap* map, void* key);
    void (*clear)  (hashmap* map);
};

void hashmap_create (hashmap* map, 
                     pfnhash hashfunc, 
                     pfndestroy destroykeyfunc, 
                     pfndestroy destroyfunc, 
                     pfncopy copykeyfunc, 
                     pfncopy copyfunc, 
                     pfncompare keycomparefunc, 
                     pfncompare comparefunc);
//!IMPOTANT: for this macro to work properly the folowing functions for it must be defined
// before calling hashmap_create
// T <- type
// uint64_t __hashmap_hash_T   (hashmap* map, const void* data, uint64_t length, uint64_t seed0, uint64_t seed1);
// void     __hashmap_destroy_T(void* pval);
// void*    __hashmap_copy_T   (void* pval);
// int      __hashmap_compare_T(void* a, void* b);
// these types have to be created both for key and value
#define HASHMAP_CREATE_MACRO(map, TKey, TVal) hashmap_create((map), \
    &__hashmap_hash_ ## TKey, \
    &__hashmap_destroy_ ## TKey, \
    &__hashmap_destroy_ ## TVal, \
    &__hashmap_copy_ ## Tkey, \
    &__hashmap_copy_ ## TVal, \
    &__hashmap_compare_ ## TKey, \
    &__hashmap_compare_ ## TVal  \
);

void hashmap_destroy(hashmap* map);

// Default functions
uint64_t SIP64(const uint8_t *in, const size_t inlen, uint64_t seed0, uint64_t seed1);

uint64_t __hashmap_hash_int     (hashmap* map, const void* data, uint64_t length, uint64_t seed0, uint64_t seed1);
uint64_t __hashmap_hash_long    (hashmap* map, const void* data, uint64_t length, uint64_t seed0, uint64_t seed1);
uint64_t __hashmap_hash_cstring (hashmap* map, const void* data, uint64_t length, uint64_t seed0, uint64_t seed1);
uint64_t __hashmap_hash_string  (hashmap* map, const void* data, uint64_t length, uint64_t seed0, uint64_t seed1);
uint64_t __hashmap_hash_vector  (hashmap* map, const void* data, uint64_t length, uint64_t seed0, uint64_t seed1);

void __hashmap_destroy_default  (void*  pval);
void __hashmap_destroy_string   (string* pval);
void __hashmap_destroy_vector   (vector* pval);

void* __hashmap_copy_int    (void* pval);
void* __hashmap_copy_long   (void* pval);
void* __hashmap_copy_cstring(const char* pval);
void* __hashmap_copy_string (string* pval);
void* __hashmap_copy_vector (vector* pval);

int __hashmap_compare_int    (void* a, void* b);
int __hashmap_compare_long   (void* a, void* b);
int __hashmap_compare_cstring(const char* a, const char* b);
int __hashmap_compare_string (string* a, string* b);
int __hashmap_compare_vector (vector* a, vector* b);

#define __hashmap_hash_default    (SIP64)
#define __hashmap_hash_int        __hashmap_hash_default
#define __hashmap_hash_long       __hashmap_hash_default
#define __hashmap_destroy_int     __hashmap_destroy_default
#define __hashmap_destroy_long    __hashmap_destroy_default

#endif//_SKLC_LIB_HASHMAP_H_