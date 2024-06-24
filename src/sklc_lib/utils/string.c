#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sklc_lib/utils/string.h>

uint64_t StringLength(const char* str) {
    return (uint64_t)strlen(str);
}

void StringCreate(string* ret, const char* str) {
    StringCreateEx(ret, str, StringLength(str), true);
}

/// @brief Advanced version of StringCreate func
/// @param ret pointer to a var where string will be placed, cannot be null or the pgm will crash
/// @param str CString,
/// @param len length of a CString
/// @param allocate tells the func if it should allocate a copy of that string(own it), or not
void StringCreateEx(string* ret, const char* str, uint64_t len, bool allocate) {
    assert(ret != NULL);
    assert(str != NULL);
    string _ret = {0};
    if(allocate) {
        _ret.data = malloc(len + 1);// len + '\0'
        _ret.len = len;
        memcpy(_ret.data, str, len + 1);
        _ret.own = true;
    } else {
        _ret.data = (char*)str;
        _ret.len = len;
        _ret.own = false;
    }

    StringDestroy(ret);
    *ret = _ret;
}

void StringDestroy(string* str) {
    assert(str != NULL);
    if(!str->own) {
        *str = (string){0};
        return;
    }
    if(str->data != NULL) free(str->data);
    *str = (string){0};
}

void StringDuplicate(string* ret, string source) {
    StringCreateEx(ret, source.data, source.len, true);
}

/// @brief concatenates 2 strings together and writes the result to ret
/// @param ret result
/// @param str1 string must be initialized
/// @param str2 same as str1
void StringAdd(string* ret, string str1, string str2) {
    string _ret = {0};
    _ret.own = true;
    _ret.len = str1.len + str2.len;
    _ret.data = malloc(_ret.len + 1);// + '\0'
    memcpy(_ret.data, str1.data, str1.len);
    memcpy(_ret.data + str1.len, str2.data, str2.len);
    _ret.data[_ret.len] = '\0';
    StringDestroy(ret);
    *ret = _ret;
}

void StringJoin(string* ret, vector strings) {
    string _ret = {0};
    uint64_t _ret_len = 0;
    for(int i = 0; i < strings.length; i++) {
        string* str = strings.get_at(&strings, i);
        _ret_len += str->len;
    }

    _ret.data = malloc(_ret_len + 1);
    _ret.data[_ret_len] = '\0';
    char* data = _ret.data;
    for(int i = 0; i < strings.length; i++) {
        string* str = strings.get_at(&strings, i);
        memcpy(data, str->data, str->len);
        data+=str->len;
    }
    
    StringDestroy(ret);
    *ret = _ret;
}

void StringSlice(string* ret, string str, uint64_t start, uint64_t end) {
    StringCreateEx(ret, str.data + start, end - start, true);
}

vector StringSplit(string str, string separator) {
    vector ret = _vector_create(1, sizeof(string),
        __vector_def_val_dtor,
        __vector_def_val_cpy,
        __vector_def_cmp
    );

    if (str.data == NULL || separator.data == NULL || separator.len == 0)
        return ret;

    uint64_t last_start = 0;
    for (uint64_t i = 0; i < str.len; ++i) {
        bool is_separator = false;
        for (uint64_t j = 0; j < separator.len; ++j) {
            if (str.data[i] == separator.data[j]) {
                is_separator = true;
                break;
            }
        }

        if (is_separator) {
            string segment = {0};
            StringCreateEx(&segment, str.data + last_start, i - last_start, true);
            ret.push_back(&ret, &segment);

            last_start = i + separator.len;
            i += separator.len - 1;
        }
    }
    if (last_start < str.len) {
        string segment = {0};
        StringCreateEx(&segment, str.data + last_start, str.len - last_start, true);
        ret.push_back(&ret, &segment);
    }

    return ret;
}

bool StringEquals(string str1, string str2) {
    if(str1.len != str2.len) return false;
    for(uint64_t i = 0; i < str1.len; ++i) {
        if(str1.data[i] != str2.data[i]) return false;
    }
    return true;
}

int StringFind(string str, string to_find, int index) {
    if (to_find.len == 0 || str.len < to_find.len || index <= 0) {
        return -1;
    }

    int occurrence = 0; // Counter for occurrences of to_find
    for (uint64_t i = 0; i <= str.len - to_find.len; ++i) {
        bool found = true;
        for (uint64_t j = 0; j < to_find.len; ++j) {
            if (str.data[i + j] != to_find.data[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            occurrence++;
            if (occurrence == index) {
                return (int)i; // Found the index-th occurrence
            }
            // Skip ahead to the end of the current occurrence to avoid overlapping matches
            i += to_find.len - 1;
        }
    }
    printf("-> to_find not found or index-th occurrence not found, returning -1\n");
    return -1; // to_find not found or index-th occurrence not found
}

int  StringCompare(string str1, string str2) {
    if(str1.len != str2.len) return str1.len - str2.len;
    for(uint64_t i = 0; i < str1.len; ++i) {
        if(str1.data[i] != str2.data[i]) return str1.data[i] - str2.data[i];
    }
    return 0;
}

void StringToUpper(string* ret, string str) {
    string _ret = {0};
    StringDuplicate(&_ret, str);
    char* data = _ret.data;
    for(int i = 0; i < _ret.len; i++) {
        if(data[i] < 'a' || data[i] > 'z') {
            continue;
        }
        data[i] -= 32;
    }
    StringDestroy(ret);
    *ret = _ret;
}

void StringToLower(string* ret, string str) {
    string _ret = {0};
    StringDuplicate(&_ret, str);
    char* data = _ret.data;
    for(int i = 0; i < _ret.len; i++) {
        if(data[i] < 'A' || data[i] > 'Z') {
            continue;
        }
        data[i] += 32;
    }
    StringDestroy(ret);
    *ret = _ret;
}

void StringReverse(string* ret, string str) {
    string _ret = {0};  
    ret->data = malloc(str.len + 1);
    ret->data[str.len] = '\0';
    int j = 0;
    for(int i = str.len; i > 0; i--) {
        ret->data[j] = str.data[i];
        j++;
    }
    StringDestroy(ret);
    *ret = _ret;
}

bool StringEndsWith(string str, string with) {
    if(str.len < with.len) return false;
    int index_to_search_from = str.len - with.len;
    string to_search = STRING_VIEW(str.data + index_to_search_from, with.len);
    int found = StringFind(to_search, with, 1);
    if(found >= 0) return true;
    return false;
}