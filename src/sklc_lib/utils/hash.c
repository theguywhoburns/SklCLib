#include <sklc_lib/utils/hash.h>

/*
unsigned u32 h = 0;
    unsigned u32 g;

    for (; data_length > 0; data_length--) {
        h = (h << 5) + *data++;
        if ((g = h & 0xf0000000) != 0)
        h = (h ^ (g >> 24)) ^ g;
    }

    return h;
*/

u32 hash_ccp_u32_u32ernal(const char* data, u32 data_length) {
    u32 hash1 = 5381;
    u32 hash2 = hash1;

    for(u32 i = 0; i < data_length && data[i] != '\0'; i += 2) {
        hash1 = ((hash1 << 5) + hash1) ^ data[i];
        if (i == data_length - 1 || data[i+1] == '\0')
            break;
            hash2 = ((hash2 << 5) + hash2) ^ data[i+1];
        }

    return hash1 + (hash2*1566083941);   
}

#pragma region etc

u32 hash_array_ccp_u32(const char* data, u32 array_length) {
    u32 data_length = string_strlen(data);

    u32 ret = hash_ccp_u32_u32ernal(data, data_length);

    ret = ret % array_length;

    return ret;
}

u32 hash_array_string_u32(string data, u32 array_length) {
    u32 ret = hash_ccp_u32_u32ernal(string_c_str(data), data.length);

    ret = ret % array_length;
    
    return ret;
}

u32 hash_array_custom_data_u32(void* data, u32 data_size, u32 array_length) {
    u32 ret = hash_ccp_u32_u32ernal(data, data_size);

    ret = ret % array_length;
    
    return ret;
}

u32 hash_ccp_u32(const char* data) {
    u32 data_length = string_strlen(data);
    return hash_ccp_u32_u32ernal(data, data_length);
}

u32 hash_string_u32(string data) {
    return hash_ccp_u32_u32ernal(string_c_str(data), data.length);
}

u32 hash_custom_data_u32(void* data, u32 data_size) {
    return hash_ccp_u32_u32ernal(data, data_size);
}

#pragma endregion etc