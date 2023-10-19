#ifndef _SKLC_LIB_STRING_H_
#define _SKLC_LIB_STRING_H_

#include <stdbool.h>

typedef unsigned short wchar;

typedef struct _string {
    char* str_data;
    unsigned long long length;
} string;

typedef struct _wstring {
    unsigned short* wstr_data;
    unsigned long long length;
} wstring;

#pragma region string
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
bool string_equals_str_str(string str1, string str2);
bool string_equals_str_ccp(string str1, const char* str2);
bool string_equals_ccp_ccp(const char* str1, const char* str2);
#pragma endregion string

#pragma region wstring
wstring wstring_create_wcp(const wchar* value);
wstring wstring_create_wstr(wstring value);
void wstring_destroy(wstring* str);
void wstring_set_wcp(wstring* str, const wchar* value);
void wstring_set_wstr(wstring* str, wstring value);
void wstring_add_wcp_wcp(wstring* out_str, const wchar* str1, const wchar* str2);
void wstring_add_wstr_wcp(wstring* out_str, wstring str1, const wchar* str2);
void wstring_add_wcp_wstr(wstring* out_str, const wchar* str1, wstring str2);
void wstring_add_wstr_wstr(wstring* out_str, wstring str1, wstring str2);
const wchar* wstring_wc_str(wstring str);
bool wstring_equals_wstr_wstr(wstring str1, wstring str2);
bool wstring_equals_wstr_wcp(wstring str1, const wchar* str2);
bool wstring_equals_wcp_wcp(const wchar* str1, const wchar* str2);
#pragma endregion wstring

#endif//_SKLC_LIB_STRING_H_