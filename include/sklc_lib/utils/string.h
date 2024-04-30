#ifndef _SKLC_LIB_STRING_H_
#define _SKLC_LIB_STRING_H_
#include <sklc_lib/defines.h>
#include <sklc_lib/utils/vector.h>
typedef struct string {
    char* data;
    uint64_t len;
    //true if owns memory, otherwise false
    bool own;
} string;

// Creates a string view that doesn't own it's memory
#define STRING_VIEW(ccp, length) (string){.data = (ccp), .len = (length), .own = false}

uint64_t StringLength(const char* str);

void StringCreate(string* ret, const char* str);
/// @brief Advanced version of StringCreate func
/// @param ret pointer to a var where string will be placed, cannot be null or the pgm will crash
/// @param str CString,
/// @param len length of a CString
/// @param allocate tells the func if it should allocate a copy of that string(own it), or not
void StringCreateEx(string* ret, const char* str, uint64_t len, bool allocate);
void StringDestroy(string* str);
void StringDuplicate(string* ret, string source);

/// @brief concatenates 2 strings together and writes the result to ret
/// @param ret result
/// @param str1 string, if it isn't the same variable as ret, then it doesnt need to own it's memory 
/// @param str2 same as str1
void StringAdd(string* ret, string str1, string str2);
void StringSlice(string* ret, string str, uint64_t start, uint64_t end);
vector StringSplit(string str, string separator);
vector StringSplitEx(string str, uint64_t amount_of_separators, string* separators);

bool StringEquals(string str1, string str2);
int StringFind(string str, string to_find, int id);

#endif//_SKLC_LIB_STRING_H_