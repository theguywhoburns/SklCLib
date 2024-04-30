#ifndef _SKLC_LIB_MATH_SKLC_MATH_TYPES_H_
#define _SKLC_LIB_MATH_SKLC_MATH_TYPES_H_

#include <sklc_lib/defines.h>

#pragma region vectors

typedef union _vec2u {
    float data[2];
    union 
    {
        struct {
            union {
            // The first element.
            float x, r, s, u;
        };
        union {
            // The second element.
            float y, g, t, v;
        };
        };
    };
      
} vec2;

typedef union _vec3u {
    float data[3];
    union 
    {
        struct {
            union {
                // The first element.
                float x, r, s, u;
            };
            union {
                // The second element.
                float y, g, t, v;
            };
            union {
                // The third element.
                float z, b, p, w;
            };
        };
    };
      
} vec3;

typedef union _vec4u {
    float data[4];
    union 
    {
        struct {
            union {
                // The first element.
                float x, r, s;
            };
            union {
                // The second element.
                float y, g, t;
            };
            union {
                // The third element.
                float z, b, p;
            };
            union {
                // The fourth element.
                float w, a, q;
            };
        };
    };
      
} vec4;

typedef union _vec2du {
    double data[2];
    union 
    {
        struct {
            union {
            // The first element.
            double x, r, s, u;
        };
        union {
            // The second element.
            double y, g, t, v;
        };
        };
    };
      
} vec2d;

typedef union _vec3du {
    double data[3];
    union 
    {
        struct {
            union {
                // The first element.
                double x, r, s, u;
            };
            union {
                // The second element.
                double y, g, t, v;
            };
            union {
                // The third element.
                double z, b, p, w;
            };
        };
    };
      
} vec3d;

typedef union _vec4du {
    double data[4];
    union 
    {
        struct {
            union {
                // The first element.
                double x, r, s;
            };
            union {
                // The second element.
                double y, g, t;
            };
            union {
                // The third element.
                double z, b, p;
            };
            union {
                // The fourth element.
                double w, a, q;
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
    float data[4];
}mat2;

typedef union _mat3u {
    float data[9];
}mat3;

typedef union _mat4u {
    float data[16];
}mat4;

typedef union _mat2du {
    double data[4];
}mat2d;

typedef union _mat3du {
    double data[9];
}mat3d;

typedef union _mat4du {
    double data[16];
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
    float data;
    struct {
        float width;        
        float height;        
        float left;        
        float top;        
    };
} rectf;

typedef union _rectdu {
    double data;
    struct {
        double width;        
        double height;        
        double left;        
        double top;        
    };
} rectd;

#pragma endregion rects


typedef vec4 quat;
typedef vec4d quatd;


#endif//_SKLC_LIB_MATH_SKLC_MATH_TYPES_H_