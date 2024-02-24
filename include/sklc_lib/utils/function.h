#ifndef _SKLC_LIB_FUNCTION_H_
#define _SKLC_LIB_FUNCTION_H_

#include <sklc_lib/defines.h>

#define FUNCTION_CAST(void_pointer, return_type, ...) ((return_type(*)(__VA_ARGS__))void_pointer)


/// Must be done like that cus ma fucking vectors treat the function as an address to some variable(will fix that later(maybe(no i will not)))
/// @brief function structure, use this in FUNCTION_CAST and in vectors
/// @param func_ptr the function pointer
/// @attention can be used to call any function, but don't forget to recast when you're doing this
/// @attention example: (bool (*test)(bool a, int b))()
typedef struct function {
    void* func_ptr;
} function;

#endif//_SKLC_LIB_FUNCTION_H_