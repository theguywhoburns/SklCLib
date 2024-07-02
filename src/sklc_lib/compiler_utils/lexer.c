#include <sklc_lib/compiler_utils/lexer.h>

bool IsSpace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool IsSeparator(char c) {
	switch (c) {
	case ' ':
	case '\t':
	case '\n':
	case '\r':
	case '(':
	case ')':
	case '{':
	case '}':
	case '[':
	case ']':
	case ',':
	case ';':
	case '.':
	case '-':
	case '=':
	case '+':
	case '*':
	case '/':
	case '%':
	case '&':
	case '^':
	case '|':
	case '!':
	case '<':
	case '>':
	case '?':
	case ':':
	case '"':
	case '\'':
	case '`':
	case '\\':
	case '~':
	case '#':
	case '$':
	case '@':
		return true;
	default:
		return false;
	}
}

char* LexString(TokenStream* ts, FILE* f, size_t* line, size_t* col) {
  char* ret = NULL;
  size_t len = 0;
  size_t capacity = 256; // Initial buffer size

  ret = malloc(capacity);
  if (!ret) {
    tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory allocation failure")));
    return NULL;
  }

  char c = (char)fgetc(f);
  while (c != '"' && c != EOF) {
    if (c == '\n') {
      (*line)++;
      (*col) = 0;
			continue;
    } else if (c == '\\') {
   		c = (char)fgetc(f);
     	if (c == EOF) {
        tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Unexpected EOF after escape character")));
        free(ret);
        return NULL;
      }
      switch (c) {
      case 'n': c = '\n'; break;
      case 't': c = '\t'; break;
      case 'r': c = '\r'; break;
      case '\\': c = '\\'; break;
      case '"': c = '"'; break;
      // Add more escape sequences as needed
      default: break; // Unknown escape sequence
      }
    }

    // Append character to the buffer
    if (len + 1 >= capacity) { // Check if the buffer is full
      capacity *= 2; // Double the buffer size 
      char* new_ret = malloc(capacity);
      if (!new_ret) {
        free(ret);
		free(new_ret);
        tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory reallocation failure")));
        return NULL;
      }
	  memcpy(new_ret, ret, len);
	  free(ret);
	  ret = new_ret;
    }

    ret[len++] = c;
    (*col)++;
    c = (char)fgetc(f);
	}

  
  /*
  // Check if the length is more than 20% less than the capacity
  if (len < capacity * 0.8) {
    char* new_ret = malloc(len + 1); // Reallocate to fit the actual string length
    if (!new_ret) {
      free(ret);
	  free(new_ret);
      tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory reallocation failure")));
      return NULL;
    }
	memcpy(new_ret, ret, len);
    ret = new_ret;
  }
  */

  ret[len] = '\0'; // Null-terminate the string
  return ret;
}

Token LexNumber(char start_c, TokenStream* ts, FILE* f, size_t* line, size_t* col) {
	Token ret = {0};
	ret.type = TOKEN_NUMBER;
	ret.data = malloc(256);
	if (!ret.data) {
		tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory allocation failure")));
		return ret;
	}
	(*col)++;
	char c = start_c;
	char* data = ret.data;
	int i = 0;
	for(; c >= '0' && c <= '9' && i < 255; i++) {
		if(c == EOF) {
			tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Unexpected EOF after number")));
			free(data);
			ret = (Token){ 0 };
			return ret;
		}
		data[i] = c;
		(*col)++;
		c = (char)fgetc(f);
	}
	
	// Set the file offset to offset -1
	fseek(f, -1, SEEK_CUR);

	data[i] = '\0';
	ret.datalen = i;
	return ret;
}

char* LexIdentifier(char start_c, TokenStream* ts, FILE* f, size_t* line, size_t* col) {
	char* ret = NULL;
  size_t len = 0;
  size_t capacity = 256; // Initial buffer size

  ret = malloc(capacity);
  if (!ret) {
    tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory allocation failure")));
    return NULL;
	}
	char c = start_c;
  while (!IsSeparator(c) && c != EOF) {
    /*
    // Append character to the buffer
    if (len + 1 >= capacity) { // Check if the buffer is full
		capacity += 256; // Double the buffer size 
		char* new_ret = malloc(capacity);
		if (!new_ret) {
			free(ret);
			free(new_ret);
			tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory reallocation failure")));
			return NULL;
		}
		memcpy(new_ret, ret, len);
		free(ret);
		ret = new_ret;
    }
	*/
    ret[len++] = c;
    (*col)++;
		c = (char)fgetc(f);
	}
	// Set the file offset to offset -1
	fseek(f, -1, SEEK_CUR);
  /*
  // Check if the length is more than 20% less than the capacity
  if (len < capacity * 0.8) {
    char* new_ret = malloc(len + 1); // Reallocate to fit the actual string length
    if (!new_ret) {
      free(ret);
	  free(new_ret);
      tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory reallocation failure")));
      return NULL;
    }
	memcpy(new_ret, ret, len);
    ret = new_ret;
  }
  */

  ret[len] = '\0'; // Null-terminate the string

  return ret;
}

Token LexNextToken(TokenStream* ts, FILE* f, size_t* line, size_t* col) {
	Token ret = {0};
	char c = (char)fgetc(f);
	while (c == ' ' || c=='\t' || c == '\n' || c == '\r') {
		if(c == '\n') {
			(*line)++;
			(*col) = 0;
		}
		c = (char)fgetc(f);
		(*col)++;
	}
	if(c == EOF) {
		ret.type = TOKEN_EOF;
		return ret;
	}
	switch (c) {
	case '(':
	case ')':
	case '{':
	case '}':
	case '[':
	case ']':
	case ',':
	case ';':
	case '.':
	case '-':
	case '=':
	case '+':
	case '*':
	case '/':
	case '%':
	case '&':
	case '^':
	case '|':
	case '!':
	case '<':
	case '>':
	case '?':
	case ':':
	case '\'':
	case '`':
	case '\\':
	case '~':
	case '#':
	case '$':
	case '@':
		col++;
		ret.type = TOKEN_SYMBOL;
		ret.data = malloc(2);
		if (!ret.data) {
			tinyvec_push(Error, ts->err, Error_Create(*line, *col, ts->file_name, STRING_VIEW("Memory allocation failure")));
			ret.type = TOKEN_EOF;

			return ret;
		}
		ret.data[0] = c;
		ret.data[1] = '\0';
		ret.datalen = 1;
		(*col)++;
		break;
	case '"': {
		col++;
		ret.type = TOKEN_STRING;
		ret.data = LexString(ts, f, line, col);
		if(ret.data == NULL) {
			ret.type = TOKEN_EOF;
			return ret;
		}
		ret.datalen = strlen(ret.data);
		return ret;
	}break;
	default:
		if(c >= '0' && c <= '9') {
			ret = LexNumber(c, ts, f, line, col);
			if(ret.data == NULL) {
				ret.type = TOKEN_EOF;
				return ret;
			}
			return ret;
		}
		ret.type = TOKEN_IDENTIFIER;
		ret.data = LexIdentifier(c, ts, f, line, col);
		if(ret.data == NULL) {
			ret.type = TOKEN_EOF;
			return ret;
		}
		ret.datalen = strlen(ret.data);
		return ret;
		break;
	}
	return ret;
}

TokenStream TokenStream_Create(const char* path) {
	FILE* file_handle = fopen(path, "r");
	if(file_handle == NULL) {
		return (TokenStream){0};
	}
	TokenStream ts = {0};
	ts.file_handle = file_handle;
	fseek(file_handle, 0, SEEK_END);
	ts.file_size = ftell(file_handle);
	fseek(file_handle, 0, SEEK_SET);
	StringCreate(&ts.file_name, path);
	ts.err = tinyvec_create(Error);
	// Force call LexNextToken for the first time
	ts.token = LexNextToken(&ts, file_handle, &ts.line, &ts.col);
	if(tinyvec_length(ts.err) > 0) {
		for(int i = 0; i < tinyvec_length(ts.err); i++) {
			Error err = ts.err[i];
			Error_print(&err);
			Error_Destroy(&err);
		}
		tinyvec_destroy(ts.err);
		fclose(ts.file_handle);
		StringDestroy(&ts.file_name);
		return (TokenStream){0};
	}
	return ts;
}

Token TokenStream_Next(TokenStream* ts) {
	Token ret = ts->token;
	if(ret.type == TOKEN_EOF) {
		return ret;
	}
	ts->token = LexNextToken(ts, ts->file_handle, &ts->line, &ts->col);
	return ret;
}

Token TokenStream_Peek(TokenStream* ts) {
	return ts->token;
}

void TokenStreamDisposeToken(TokenStream* ts, Token* t) {
	if(!ts || !t) return;
	if(t->data != NULL) free(t->data);
	t->data = NULL;
	t->datalen = 0;
	t->type = TOKEN_EOF;
	t->line = 0;
	t->col = 0;
}

void TokenStream_Destroy(TokenStream* ts) {
	if(!ts) return;
	if(ts->err  != NULL) { tinyvec_destroy(ts->err); ts->err = NULL; }
	if(ts->file_name.data != NULL){ StringDestroy(&ts->file_name); ts->file_name.data = NULL; }
	if(ts->file_handle  != NULL) 	{ fclose(ts->file_handle); ts->file_handle = NULL; }
	TokenStreamDisposeToken(ts, &ts->token);
}