#ifndef _SKLC_LIB_GRAPHICS_WINDOW_H_
#define _SKLC_LIB_GRAPHICS_WINDOW_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/string.h>
#include <sklc_lib/math/sklc_math.h>

// TODO: Refactor do get rid of system-specific headers!!!
#include <Windows.h>

// TODO: Cross-Platform support
typedef struct window {

    int width, height, x, y;

    int default_width;
    int default_height;

    wchar* window_name;

    // Window class info
    WNDCLASSEXW wcex;

    // Window handle
    HWND wnd_handle;

    bool is_running;

    void* wnd_context;

} *window;

window window_create(
    const char* window_name,
    int width,
    int height,
    int x,
    int y);

bool window_update(window wnd, bool update_window_data);

void window_destroy(window wnd);


#endif//_SKLC_LIB_GRAPHICS_WINDOW_H_