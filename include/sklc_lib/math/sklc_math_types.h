#ifndef _SKLC_LIB_MATH_SKLC_MATH_TYPES_H_
#define _SKLC_LIB_MATH_SKLC_MATH_TYPES_H_

#include <sklc_lib/defines.h>

#pragma region vectors

typedef union _vec2u {
    f32 data[2];
    union 
    {
        struct {
            union {
            // The first element.
            f32 x, r, s, u;
        };
        union {
            // The second element.
            f32 y, g, t, v;
        };
        };
    };
      
} vec2;

typedef union _vec3u {
    f32 data[3];
    union 
    {
        struct {
            union {
                // The first element.
                f32 x, r, s, u;
            };
            union {
                // The second element.
                f32 y, g, t, v;
            };
            union {
            // The third element.
            f32 z, b, p, w;
            };
        };
    };
      
} vec3;

typedef union _vec4u {
    f32 data[4];
    union 
    {
        struct {
            union {
                // The first element.
                f32 x, r, s;
            };
            union {
                // The second element.
                f32 y, g, t;
            };
            union {
                // The third element.
                f32 z, b, p;
            };
            union {
                // The fourth element.
                f32 w, a, q;
            };
        };
    };
      
} vec4;

typedef union _vec2du {
    f64 data[2];
    union 
    {
        struct {
            union {
            // The first element.
            f64 x, r, s, u;
        };
        union {
            // The second element.
            f64 y, g, t, v;
        };
        };
    };
      
} vec2d;

typedef union _vec3du {
    f64 data[3];
    union 
    {
        struct {
            union {
                // The first element.
                f64 x, r, s, u;
            };
            union {
                // The second element.
                f64 y, g, t, v;
            };
            union {
            // The third element.
            f64 z, b, p, w;
            };
        };
    };
      
} vec3d;

typedef union _vec4du {
    f64 data[4];
    union 
    {
        struct {
            union {
                // The first element.
                f64 x, r, s;
            };
            union {
                // The second element.
                f64 y, g, t;
            };
            union {
                // The third element.
                f64 z, b, p;
            };
            union {
                // The fourth element.
                f64 w, a, q;
            };
        };
    };
      
} vec4d;

#pragma endregion vectors
#pragma region matricies
typedef union _mat2u {
    f32 data[4];
}mat2;

typedef union _mat3u {
    f32 data[9];
}mat3;

typedef union _mat4u {
    f32 data[16];
}mat4;

typedef union _mat2du {
    f64 data[4];
}mat2d;

typedef union _mat3du {
    f64 data[9];
}mat3d;

typedef union _mat4du {
    f64 data[16];
}mat4d;
#pragma endregion matricies

typedef vec4 quat;
typedef vec4d quatd;




#endif//_SKLC_LIB_MATH_SKLC_MATH_TYPES_H_