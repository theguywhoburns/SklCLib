#pragma once

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>

enum ErrorType {
	LEXER_ERROR,
	SYNTAX_ERROR,
	BUG,
	ERROR_MAX
};

typedef struct Error {
	uint8_t e;
	size_t line;
	size_t col;
	string file;	
	string message;
} Error;

// Will save the message string but copy the file string
Error Error_Create(size_t line, size_t col, string file, string message);
void Error_print(Error* error);
void Error_Destroy(Error* error);