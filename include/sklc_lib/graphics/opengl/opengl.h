#ifndef _SKLC_LIB_GRAPHICS_OPENGL_H_
#define _SKLC_LIB_GRAPHICS_OPENGL_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/graphics/renderer_backend.h>

b8 opengl_initialize(struct renderer_backend* backend, const char* app_name);
b8 opengl_init_wnd(window wnd);
void opengl_make_context_current(window wnd);
void opengl_swap_buffers(window wnd, b8 vsync);

void opengl_shutdown(window wnd);

#endif//_SKLC_LIB_GRAPHICS_OPENGL_H_