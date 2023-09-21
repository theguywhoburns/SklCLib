#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t (hashfunction) (const char*, size_t);
typedef struct _hash_table hash_table;

hash_table *hash_table_cheate(uint32_t size, hashfunction *hf);
void hash_table_destroy(hash_table* ht);
void hash_table_print  (hash_table* ht);
bool hash_table_insern(hash_table* ht, const char *key, size_t keylen, void *obj);
void* hash_table_lookup(hash_table* ht, const char* key, size_t keylen);

#endif //_HASH_TABLE_H_