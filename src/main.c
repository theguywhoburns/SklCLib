#include <sklc_lib/string.h>

#include <stdio.h>

int main() {
    string str1 = string_create_ccp("LOL");
    printf("%s\n", string_c_str(str1));
    string_set_ccp(&str1, "Hello, and welcome ");
    printf("%s\n", string_c_str(str1));
    string_add_str_ccp(&str1, str1, "to my ");
    printf("%s\n", string_c_str(str1));
    string str2 = string_create_ccp("library: ");
    printf("%s\n", string_c_str(str2));
    string str3 = string_create_ccp("SklC Lib");
    printf("%s\n", string_c_str(str3));
    string str4 = string_create_str(str3);
    printf("%s\n", string_c_str(str4));

    string_add_str_str(&str2, str2, str4);
    printf("%s\n", string_c_str(str2));
    string_add_str_str(&str1, str1, str2);
    printf("%s\n", string_c_str(str1));
    string_destroy(&str1);
    string_destroy(&str2);
    string_destroy(&str3);
    string_destroy(&str4);
    return 0;
}