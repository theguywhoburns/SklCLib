#ifndef _SKLC_LIB_GRAPHICS_RENDERER_BACKEND_H_
#define _SKLC_LIB_GRAPHICS_RENDERER_BACKEND_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/graphics/window.h>

typedef enum renderer_type {
    RENDERER_BACKEND_TYPE_OPENGL=0,
    RENDERER_BACKEND_TYPE_DX_9 = 1,
    RENDERER_BACKEND_TYPE_DX_10= 2,
    RENDERER_BACKEND_TYPE_DX_11= 3,
    RENDERER_BACKEND_TYPE_DX_12= 4,
    RENDERER_BACKEND_TYPE_VULKAN=5
} renderer_type;

typedef struct renderer_backend {
    u64 frame_number;

    b8 (*initialize)(struct renderer_backend* backend, const char* app_name);
    void (*shutdown)(struct renderer_backend* backend);
    void (*resized)(struct renderer_backend* backend, u16 width, u16 height);

    b8 (*begin_frame)(struct renderer_backend* backend, f32 delta_time);
    //void (*update_global_state)(mat4 projection, mat4 view, vec3 view_position, vec4 ambient_colour, i32 mode);
    b8 (*end_frame)(struct renderer_backend* backend, f32 delta_time);

} renderer_backend;

void renderer_backend_create(renderer_type type, renderer_backend* out_renderer_backend);

#endif//_SKLC_LIB_GRAPHICS_RENDERER_BACKEND_H_