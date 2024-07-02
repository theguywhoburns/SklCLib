#include <sklc_lib/compiler_utils/lexer.h>
#include <sklc_lib/utils/logger.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    TokenStream* ts = TokenStream_Create("test.sklc", &argc);
    if(ts == NULL) {
        printf("Failed to create token stream\n");
        return 1;
    }
    Token t = TokenStream_Next(ts);
    while (t.type != TOKEN_EOF) {
        SKLDEBUG("%s", t.data);
        free(t.data);
        t = TokenStream_Next(ts);
        SKLDEBUG("%d", (int)t.data);
    }
    
    TokenStream_Destroy(ts);
    return 0;
}
