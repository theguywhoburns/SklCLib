#include <stdio.h>
#include <sklc_lib/graphics/window.h>

int main() {
    
    window wnd = window_create("Sklc Window Test #4 window_update func test", 800, 600, CW_USEDEFAULT, CW_USEDEFAULT);

    while(window_update(wnd)) {
    
    }

    window_destroy(wnd);    

    return 0;
}