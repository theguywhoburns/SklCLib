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
#define STRING_VIEW_(ccp, length) (string){.data = (ccp), .len = (length), .own = false}
#define STRING_VIEW(ccp) STRING_VIEW_(ccp, StringLength(ccp))
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
void StringJoin(string* ret, vector strings);
void StringSlice(string* ret, string str, uint64_t start, uint64_t end);
vector StringSplit(string str, string separator);

bool StringEquals(string str1, string str2);
int  StringCompare(string str1, string str2);
#define STRING_FIND_LAST -1
int  StringFind(string str, string to_find, int index);

void StringToUpper(string* ret, string str); 
void StringToLower(string* ret, string str); 

bool StringEndsWith(string str, string with);
void StringReverse(string* ret, string str);

void IntToString(string* ret, int64_t val);
bool StringToInt(string str, int64_t* ret);
void FloatToString(string* ret, double val);
bool StringToFloat(string str, double* ret);

INLINE bool StringIsEmpty(string str) {
    return str.len == 0;
}

#endif//_SKLC_LIB_STRING_H_