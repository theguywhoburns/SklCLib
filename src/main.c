#include <sklc_lib/compiler_utils/lexer.h>
#include <sklc_lib/utils/logger.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    TokenStream ts = TokenStream_Create("test.sklc"); 
    if(ts.file_handle == NULL) {
        printf("Failed to create token stream\n");
        return 1;
    }
    Token t = TokenStream_Next(&ts);
    while (t.type != TOKEN_EOF) {
        SKLDEBUG("%s", t.data);
        TokenStreamDisposeToken(&ts, &t);
        t = TokenStream_Next(&ts);
    }
    for (int i = 0; i < tinyvec_length(ts.err); i++) {
        Error_print(&ts.err[i]);
        Error_Destroy(&ts.err[i]);
    }
    TokenStream_Destroy(&ts);
    return 0;
}
