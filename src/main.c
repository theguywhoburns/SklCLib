#include <sklc_lib/string.h>

#include <stdio.h>

int main() {
    wstring str1 = wstring_create_wcp(L"LOL");
    wprintf(L"%s\n", wstring_wc_str(str1));
    wstring_set_wcp(&str1, L"Hello, and welcome ");
    wprintf(L"%s\n", wstring_wc_str(str1));
    wstring_add_wstr_wcp(&str1, str1, L"to my ");
    wprintf(L"%s\n", wstring_wc_str(str1));
    wstring str2 = wstring_create_wcp(L"library: ");
    wprintf(L"%s\n", wstring_wc_str(str2));
    wstring str3 = wstring_create_wcp(L"SklC Lib");
    wprintf(L"%s\n", wstring_wc_str(str3));
    wstring str4 = wstring_create_wstr(str3);
    wprintf(L"%s\n", wstring_wc_str(str4));

    wstring_add_wstr_wstr(&str2, str2, str4);
    wprintf(L"%s\n", wstring_wc_str(str2));
    wstring_add_wstr_wstr(&str1, str1, str2);
    wprintf(L"%s\n", wstring_wc_str(str1));
    wstring_destroy(&str1);
    wstring_destroy(&str2);
    wstring_destroy(&str3);
    wstring_destroy(&str4);
    return 0;
}