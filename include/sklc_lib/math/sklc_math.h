#ifndef _SKLC_LIB_MATH_SKLC_MATH_H_
#define _SKLC_LIB_MATH_SKLC_MATH_H_
#include <sklc_lib/defines.h>
#include <sklc_lib/math/sklc_math_types.h>  
#include <sklc_lib/string.h>

#define SKL_PI 3.14159265358979323846f
#define SKL_PI_2 2.0f * SKL_PI
#define SKL_HALF_PI 0.5f * SKL_PI
#define SKL_QUARTER_PI 0.25f * SKL_PI
#define SKL_ONE_OVER_PI 1.0f / SKL_PI
#define SKL_ONE_OVER_TWO_PI 1.0f / SKL_PI_2
#define SKL_SQRT_TWO 1.41421356237309504880f
#define SKL_SQRT_THREE 1.73205080756887729352f
#define SKL_SQRT_ONE_OVER_TWO 0.70710678118654752440f
#define SKL_SQRT_ONE_OVER_THREE 0.57735026918962576450f
#define SKL_DEG2RAD_MULTIPLIER SKL_PI / 180.0f
#define SKL_RAD2DEG_MULTIPLIER 180.0f / SKL_PI

// The multiplier to convert seconds to milliseconds.
#define SKL_SEC_TO_MS_MULTIPLIER 1000.0f

// The multiplier to convert milliseconds to seconds.
#define SKL_MS_TO_SEC_MULTIPLIER 0.001f

// A huge number that should be larger than any valid number used.
#define SKL_INFINITY 1e30f

// Smallest positive number where 1.0 + FLOAT_EPSILON != 0
#define SKL_FLOAT_EPSILON 1.192092896e-07f

// Output string must be destroyed after use
string conv(int val, int base);
string fconv(float val, int base); // Not implemented

f32 sin(f32 x);
f32 cos(f32 x);
f32 tan(f32 x);
f32 acos(f32 x);
f32 sqrt(f32 x);
f32 abs(f32 x);

i32 random();
i32 random_in_range(i32 min, i32 max);
f32 frandom();
f32 frandom_in_range(f32 min, f32 max);

INLINE vec2 vec2_create(f32 x, f32 y) {
    vec2 ret;
    ret.x = x;
    ret.y = y;
    return ret;    
}

INLINE vec2 vec2_one() {
    return (vec2){1.0f, 1.0f};
}

INLINE vec2d vec2d_create(f64 x, f64 y) {
    vec2d ret;
    ret.x = x;
    ret.y = y;
    return ret;    
}


#endif//_SKLC_LIB_MATH_SKLC_MATH_H_