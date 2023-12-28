#ifndef _SKLC_LIB_UTILS_HASH_H_
#define _SKLC_LIB_UTILS_HASH_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/string.h>

// Used for custom hashmap, you can use it if you want to
u32 hash_array_ccp_u32(const char* data, u32 array_length);
u32 hash_array_string_u32(string data, u32 array_length);
u32 hash_array_custom_data_u32(void* data, u32 data_size, u32 array_length);

u32 hash_ccp_u32(const char* data);
u32 hash_string_u32(string data);
u32 hash_custom_data_u32(void* data, u32 data_size);



#endif//_SKLC_LIB_UTILS_HASH_H_