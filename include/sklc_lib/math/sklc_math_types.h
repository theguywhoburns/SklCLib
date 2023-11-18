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

typedef union _vec2iu {
    i32 data[2];
    union 
    {
        struct {
            union {
            // The first element.
            i32 x, r, s, u;
        };
        union {
            // The second element.
            i32 y, g, t, v;
        };
        };
    };
      
} vec2i;

typedef union _vec3iu {
    i32 data[3];
    union 
    {
        struct {
            union {
                // The first element.
                i32 x, r, s, u;
            };
            union {
                // The second element.
                i32 y, g, t, v;
            };
            union {
                // The third element.
                i32 z, b, p, w;
            };
        };
    };
      
} vec3i;

typedef union _vec4iu {
    i32 data[4];
    union 
    {
        struct {
            union {
                // The first element.
                i32 x, r, s;
            };
            union {
                // The second element.
                i32 y, g, t;
            };
            union {
                // The third element.
                i32 z, b, p;
            };
            union {
                // The fourth element.
                i32 w, a, q;
            };
        };
    };
      
} vec4i;

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
#pragma region rects

typedef union _rectu {
    i32 data;
    struct {
        i32 width;        
        i32 height;        
        i32 left;        
        i32 top;        
    };
} rect;

typedef union _rectlu {
    i64 data;
    struct {
        i64 width;        
        i64 height;        
        i64 left;        
        i64 top;        
    };
} rectl;

typedef union _rectfu {
    f32 data;
    struct {
        f32 width;        
        f32 height;        
        f32 left;        
        f32 top;        
    };
} rectf;

typedef union _rectdu {
    f64 data;
    struct {
        f64 width;        
        f64 height;        
        f64 left;        
        f64 top;        
    };
} rectd;

#pragma endregion rects


typedef vec4 quat;
typedef vec4d quatd;


#endif//_SKLC_LIB_MATH_SKLC_MATH_TYPES_H_