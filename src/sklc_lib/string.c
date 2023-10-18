#include <string.h>
#include <stdlib.h>

#include <sklc_lib/string.h>

unsigned long long local_strlen(const char* str) {
    const char* s;
    for (s = str; *s; ++s);
    return (s - str);
}

string string_create_ccp(const char* value) {
    string ret =  {0};
    ret.length = local_strlen(value);
    ret.str_data = malloc(ret.length + 1);
    memcpy(ret.str_data, value, ret.length);
    ret.str_data[ret.length] = '\0';
    return ret;
}

string string_create_str(string value) {
    string ret = {0};
    ret.length = value.length;
    ret.str_data = malloc(value.length + 1);
    memcpy(ret.str_data, value.str_data, ret.length + 1); // ret.length + 1 = '\0'
    return ret;
}

void string_destroy(string* str) {
    free(str->str_data);
    str->length = 0;
    str->str_data = 0;
}

void string_set_ccp(string* str, const char* value) {
    string_destroy(str);
    *str = string_create_ccp(value);
}

void string_set_str(string* str, string value) {
    string_destroy(str);
    *str = string_create_str(value);
}

void string_add_ccp_ccp(string* out_str, const char* str1, const char* str2) {
    string_destroy(out_str);
    unsigned long long length1 = local_strlen(str1);
    unsigned long long length2 = local_strlen(str2);

    out_str->str_data = malloc(length1 + length2 + 1);
    out_str->length = length1 + length2;
    char* ptr = out_str->str_data;
    memcpy(ptr, str1, length1);
    ptr+= length1;
    memcpy(ptr, str2, length2);
    out_str->str_data[length1 + length2] = '\0';
}

void string_add_str_ccp(string* out_str, string str1, const char* str2) {
    string local_str1 = string_create_str(str1);
    string_destroy(out_str);
    unsigned long long length2 = local_strlen(str2);

    out_str->str_data = malloc(local_str1.length + length2 + 1);
    out_str->length = local_str1.length + length2;
    char* ptr = out_str->str_data;
    memcpy(ptr, local_str1.str_data, local_str1.length);
    ptr+= local_str1.length;
    memcpy(ptr, str2, length2);
    out_str->str_data[local_str1.length + length2] = '\0';
    string_destroy(&local_str1);
}

void string_add_ccp_str(string* out_str, const char* str1, string str2) {
    string local_str2 = string_create_str(str2);
    string_destroy(out_str);
    unsigned long long length1 = local_strlen(str1);

    out_str->str_data = malloc(local_str2.length + length1 + 1);
    out_str->length = local_str2.length + length1;
    char* ptr = out_str->str_data;
    memcpy(ptr, str1, length1);
    ptr+= length1;
    memcpy(ptr, local_str2.str_data, local_str2.length);
    out_str->str_data[local_str2.length + length1] = '\0';
    string_destroy(&local_str2);
}

void string_add_str_str(string* out_str, string str1, string str2) {
    string local_str1 = string_create_str(str1);
    string local_str2 = string_create_str(str2);
    string_destroy(out_str);
    out_str->str_data = malloc(local_str1.length + local_str2.length + 1);
    out_str->length = local_str1.length + local_str2.length;
    unsigned long long ptr = 0;
    for (unsigned long long i = 0; i < local_str1.length; ++i) {
        out_str->str_data[ptr] = local_str1.str_data[i];
        ptr++;
    }
    for (unsigned long long i = 0; i < local_str2.length; ++i) {
        out_str->str_data[ptr] = local_str2.str_data[i];
        ptr++;
    }
    out_str->str_data[local_str1.length + local_str2.length] = '\0';
    string_destroy(&local_str1);
    string_destroy(&local_str2);
}

const char* string_c_str(string str) {
    return (const char*)str.str_data;
}