#include <sklc_lib/graphics/renderer_backend.h>

#include <sklc_lib/graphics/opengl/opengl.h>

void renderer_backend_create(renderer_type type, renderer_backend* out_renderer_backend) {
    switch (type) {
    case RENDERER_BACKEND_TYPE_OPENGL: {
        out_renderer_backend->initialize = opengl_initialize;
        out_renderer_backend->shutdown = opengl_shutdown;
    }break;
    
    default:
        break;
    }
}