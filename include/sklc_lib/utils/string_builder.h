#ifndef _SKLC_LIB_UTILS_STRINGBUILDER_H_
#define _SKLC_LIB_UTILS_STRINGBUILDER_H_

#include <sklc_lib/utils/string.h>

typedef struct _StringBuilderNode _StringBuilderNode;

typedef struct StringBuilder {
	_StringBuilderNode* head;
	_StringBuilderNode* tail;
} StringBuilder;

StringBuilder* StringBuilder_Create();
void StringBuilder_Destroy(StringBuilder* strbld);
void StringBuilder_Clear(StringBuilder* strbld);

void StringBuilder_Append(StringBuilder* strbld, string str);
void StringBuilder_AppendCCP(StringBuilder* strbld, const char* str);

void StringBuilder_Concat(StringBuilder* ret, StringBuilder* strbld1, StringBuilder* strbld2);

string StringBuilder_GetResult(StringBuilder* strbld);


#endif//_SKLC_LIB_UTILS_STRINGBUILDER_H_