#ifndef _SKLC_LIB_FUNCTION_H_
#define _SKLC_LIB_FUNCTION_H_

#include <sklc_lib/defines.h>

#define FUNCTION_CAST(func, return_type, ...) ((return_type(*)(__VA_ARGS__))func)
#define FUNCTION_TYPE(return_type, ...) return_type(*)(__VA_ARGS__)
#define CREATE_FUNCTION_TYPE(name, return_type, ...) typedef return_type (*name)(__VA_ARGS__)

/// Must be done like that cus ma fucking vectors treat the function as an address to some variable(will fix that later(maybe(no i will not)))
/// @brief function structure, use this in FUNCTION_CAST and in vectors
/// @param func_ptr the function pointer
/// @attention can be used to call any function, but don't forget to recast when you're doing this
/// @attention example: (bool (*test)(bool a, int b))()
typedef struct function {
    void* func_ptr;
} function;

#endif//_SKLC_LIB_FUNCTION_H_