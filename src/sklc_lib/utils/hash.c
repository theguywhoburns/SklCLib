#include <sklc_lib/utils/hash.h>

u64 hash_ccp_u64_internal(const char* data, u64 data_length) {
    // hash stuff

    return 0; // temp
}

#pragma region etc

u64 hash_array_ccp_u64(const char* data, u64 array_length) {
    u64 data_length = string_strlen(data);

    u64 ret = hash_ccp_u64_internal(data, data_length);

    ret = ret % array_length;

    return ret;
}

u64 hash_array_string_u64(string data, u64 array_length) {
    u64 ret = hash_ccp_u64_internal(string_c_str(data), data.length);

    ret = ret % array_length;
    
    return ret;
}

u64 hash_array_custom_data_u64(void* data, u64 data_size, u64 array_length) {
    u64 ret = hash_ccp_u64_internal(data_size, data);

    ret = ret % array_length;
    
    return ret;
}

u64 hash_ccp_u64(const char* data) {
    u64 data_length = string_strlen(data);
    return hash_ccp_u64_internal(data, data_length);
}

u64 hash_string_u64(string data) {
    return hash_ccp_u64_internal(string_c_str(data), data.length);
}

u64 hash_custom_data_u64(void* data, u64 data_size) {
    return hash_ccp_u64_internal(data_size, data);
}

#pragma endregion etc