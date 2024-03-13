#include <stdio.h>
#include <sklc_lib/utils/string.h>

int main() {
    // Test your string_split functions here
    string str = string_create_ccp("apple, orange, banana", 22);
    string separator = string_create_ccp(", ", 2);

    vector result = string_split_str_str(str, separator);

    for (u64 i = 0; i < result.length; i++) {
        string* token = result.get_at(&result, i);
        printf("Token %llu: %s\n", i, string_c_str(*token));
    }

    // Clean up
    string_destroy(&str);
    string_destroy(&separator);
    for (u64 i = 0; i < result.length; i++) {
        string* token = result.get_at(&result, i);
        string_destroy(token);
    }
    vector_destroy(&result);
    return 0;
}