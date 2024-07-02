#ifndef _SKLC_LIB_JSON_H_
#define _SKLC_LIB_JSON_H_

#include <sklc_lib/defines.h>

enum JSON_TYPE {
	JSON_INVALID 	= 0b00000000,
	JSON_BOOL   	= 0b00000001,
	JSON_NULL    	= 0b00000010,
	JSON_NUMBER  	= 0b00000100,
	JSON_STRING  	= 0b00001000,
	JSON_ARRAY   	= 0b00010000,
	JSON_OBJECT   = 0b00100000,
	JSON_RAW      = 0b01000000,
};

STATIC_ASSERT(sizeof(uintptr_t) == sizeof(size_t));

typedef union JSON_VALUE {
	double num_value;
	char*  str_value;
	bool   bool_value;
} JSON_VALUE;

typedef struct JSON {
	struct JSON* next;
	struct JSON* prev;
	// For arrays and objects
	struct JSON* child;

	// JSON_TYPE
	int type;
	JSON_VALUE value;
	char* name;
} JSON;



// #define JSON_NESTING_LIMIT 1000



#endif//_SKLC_LIB_JSON_H_