#ifndef _SKLC_LIB_UTILS_HASH_H_
#define _SKLC_LIB_UTILS_HASH_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/string.h>

// Used for custom hashmap, you can use it if you want to
u64 hash_array_ccp_u64(const char* data, u64 array_length);
u64 hash_array_string_u64(string data, u64 array_length);
u64 hash_array_custom_data_u64(void* data, u64 data_size, u64 array_length);

u64 hash_ccp_u64(const char* data);
u64 hash_string_u64(string data);
u64 hash_custom_data_u64(void* data, u64 data_size);



#endif//_SKLC_LIB_UTILS_HASH_H_