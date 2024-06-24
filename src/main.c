#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/logger.h>
#include <Windows.h>
#include <stdio.h>
int main(int argc, char* argv[]) {
    
    string str = STRING_VIEW("This is a test string.wfsdfwtgrev that I.asdassd am using to test StringSplit", 57);
    vector vec = StringSplit(str, STRING_VIEW(" .", 2));

    uint64_t i;
    for (i = 0; i < vec.length; i++) {
        string* val = vec.pop_back(&vec);
        SKLDEBUG("%s", val->data);

        StringDestroy(val);
        free(val);
    }

    vector_destroy(&vec);

    return 0;
}
