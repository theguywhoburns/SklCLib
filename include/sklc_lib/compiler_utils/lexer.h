#pragma once

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/tinyvec.h>
#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/gc.h>

enum TokenType {
	TOKEN_EOF = 0, // Basically it says that TOKEN_EOF == NULL
	TOKEN_SYMBOL,  // Any special symbol like "(", ")", etc
	TOKEN_IDENTIFIER,
  TOKEN_BOOLEAN,
	TOKEN_STRING,
	TOKEN_NUMBER,
};

typedef struct Token {
	char* data; 
	size_t datalen;
	size_t line;
	size_t col;
	uint8_t type;
} Token;

typedef struct TokenStream TokenStream;

/**
 * @brief Creates a new TokenStream object for reading tokens from the file specified by `path`.
 * 
 * @param path The path to the file to read tokens from.
 * @return A pointer to the newly created TokenStream object, or `NULL` if an error occurred.
 */
TokenStream* TokenStream_Create(const char* path, int* argc_start);

/**
 * @brief Returns the next token from the TokenStream.
 * 
 * If the end of the file is reached, a token with TokenType::TOKEN_EOF(0/NULL) is returned.
 * 
 * @param token The TokenStream from which to read the next token.
 * @return The next token from the TokenStream.
 */
Token TokenStream_Next(TokenStream* token);

/**
 * @brief Returns the next token from the TokenStream without advancing the stream.
 * 
 * If the end of the file is reached, a token with TokenType::TOKEN_EOF is returned.
 * 
 * @param token The TokenStream from which to read the next token.
 * @return The next token from the TokenStream.
 */
Token TokenStream_Peek(TokenStream* token);

void TokenStream_Destroy(TokenStream* ts);