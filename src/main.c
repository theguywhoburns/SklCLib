#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Предполагаемые определения функций из sklc_lib
void StringSlice(string* slice, string str, size_t start, size_t end);
void vector_destroy(vector* vec);

// Функция для проверки равенства двух строк
bool string_equals(string str1, string str2) {
    if (str1.len != str2.len) return false;
    return memcmp(str1.data, str2.data, str1.len) == 0;
}

// Тестовая функция
void test_string_split() {
    // Исходная строка для разделения
    string testStr = {"This,is.a:test-string.piaijfp"};
    
    // Массив разделителей
    string separators[] = {
        STRING_VIEW(" ", 1), 
        STRING_VIEW(".", 1), 
        STRING_VIEW(",", 1), 
        STRING_VIEW(";", 1), 
        STRING_VIEW(":", 1), 
        STRING_VIEW("-", 1)
        };
    
    // Разделение строки
    vector result = StringSplitEx(testStr, 6, separators);
    
    // Вывод результатов
    for (size_t i = 0; i < result.length; ++i) {
        printf("Result[%zu]: %.*s\n", i, ((string*)result.data)[i].len, ((string*)result.data)[i].data);
    }
    
    for (size_t i = 0; i < result.length; ++i) {
        StringDestroy(&((string*)result.data)[i]);
    }

    // Освобождение памяти
    vector_destroy(&result);
}

int main() {
    test_string_split();
    return 0;
}