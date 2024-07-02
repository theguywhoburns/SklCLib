#include <sklc_lib/compiler_utils/Error.h>
#include <sklc_lib/utils/console.h>
#include <stdio.h>

Error Error_Create(size_t line, size_t col, string file, string message) {
	Error ret = {0};
	ret.e = LEXER_ERROR;
	ret.line = line;
	ret.col = col;
	StringDuplicate(&ret.file, file);
	ret.message = message;
	return ret;
}

void Error_print(Error* error) {
	const char* err_type_strs[ERROR_MAX] = {
		"LEXER_ERROR",
		"SYNTAX_ERROR",
		"BUG"
	};
	ResetConsoleColor();
	SetConsoleColor(ConsoleColorBlack, ConsoleColorLightPurple, ConsoleAttributeNormal);
	putc('[', stderr);
	SetConsoleColor(ConsoleColorBlack, ConsoleColorRed, ConsoleAttributeNormal);
	fputs(err_type_strs[error->e], stderr);
	SetConsoleColor(ConsoleColorBlack, ConsoleColorLightPurple, ConsoleAttributeNormal);
	putc(']', stderr);
	SetConsoleColor(ConsoleColorBlack, ConsoleColorGreen, ConsoleAttributeNormal);
	putc(':', stderr);
	SetConsoleColor(ConsoleColorBlack, ConsoleColorWhite, ConsoleAttributeNormal);
	fprintf(stderr, " %s:%zu:%zu: %s\n", error->file.data, error->line, error->col, error->message.data);
	ResetConsoleColor();
}

void Error_Destroy(Error* error) {
	StringDestroy(&error->message);
	StringDestroy(&error->file);
}
