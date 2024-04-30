// In window.h

#ifndef _SKLC_LIB_WINDOW_H_
#define _SKLC_LIB_WINDOW_H_

#include <sklc_lib/defines.h>

typedef struct Window {
    void* internal; // Platform/renderer specific data
    // Common window attributes
    int width;
    int height;
    char* title;
    bool ShouldClose;
    // ... other common attributes and methods ...
} Window;

// Platform-specific window creation and management functions
Window* CreateSklcWindow(int width, int height, const char* title);
void DestroySklcWindow(Window* window);
void ProcessSklcWindowMessages();
// ... other platform-agnostic window functions ...

#endif//_SKLC_LIB_WINDOW_H_
