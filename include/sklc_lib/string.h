#ifndef _SKLC_LIB_STRING_H_
#define _SKLC_LIB_STRING_H_

#include <stdbool.h>


typedef struct _string {
    char* str_data;
    unsigned long long length;
} string;

// Yet to implement......

string string_create_ccp(const char* value);
string string_create_str(string value);

void string_destroy(string* str);

void string_set_ccp(string* str, const char* value);
void string_set_str(string* str, string value);

void string_add_ccp_ccp(string* out_str, const char* str1, const char* str2);
void string_add_str_ccp(string* out_str, string str1, const char* str2);
void string_add_ccp_str(string* out_str, const char* str1, string str2);
void string_add_str_str(string* out_str, string str1, string str2);

const char* string_c_str(string str);

#endif//_SKLC_LIB_STRING_H_