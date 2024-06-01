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

void StringSlice(string* ret, string str, uint64_t start, uint64_t end) {
    StringCreateEx(ret, str.data + start, end - start, true);
}

vector StringSplit(string str, string separator) {

}

vector StringSplitEx(string str, uint64_t amount_of_separators, string* separators) {
    vector ret = _vector_create(sizeof(string), amount_of_separators + 1);
    ret.resize(&ret, amount_of_separators + 1);
    uint64_t count = 0;
    uint64_t start = 0;
    for (uint64_t i = 0; i < str.len; ++i) {
        bool found = false;
        for (uint64_t j = 0; j < amount_of_separators; ++j) {
            if (str.data[i] == separators[j].data[0]) {
                found = true;
                StringSlice(&(((string*)ret.data)[count]), str, start, i);
                count++;
                start = i + separators[j].len;
                i += separators[j].len - 1;
                break;
            }
        }
        if (!found) {
            if (i == str.len - 1) {
                StringSlice(&((string*)ret.data)[count], str, start, i + 1);
            }
        }
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

int StringFind(string str, string to_find, int id) {
    if (to_find.len == 0 || str.len < to_find.len || id <= 0) {
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
            if (occurrence == id) {
                return (int)i; // Found the id-th occurrence
            }
            // Skip ahead to the end of the current occurrence to avoid overlapping matches
            i += to_find.len - 1;
        }
    }
    return -1; // to_find not found or id-th occurrence not found
}