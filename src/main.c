#include <stdio.h>
#include <sklc_lib/graphics/opengl/opengl.h>
#include <sklc_lib/internal/glad/glad.h>

int main() {
    opengl_initialize(NULL, NULL);
    window wnd = window_create("Sklc Window Test #5 opengl test", 800, 600, CW_USEDEFAULT, CW_USEDEFAULT);

    opengl_init_wnd(wnd);
    opengl_make_context_current(wnd);

    while(window_update(wnd, true)) {
        glClearColor(0.04f, 0.07f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        opengl_swap_buffers(wnd, true);
    }
    
    opengl_shutdown(wnd);
    window_destroy(wnd);    

    return 0;
}