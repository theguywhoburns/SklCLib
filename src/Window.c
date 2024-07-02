#include <sklc_lib/Window.h>

// In window_windows.c

#ifdef SKLC_PLATFORM_WINDOWS
#include <Windows.h>
#include <sklc_lib/utils/logger.h>
#include <stdio.h>

#define WINDOW_PROP L"SKLCWND"

// Internal structure to hold Win32-specific window data
typedef struct WindowsInternal {
    HWND hwnd;
    HINSTANCE hInstance;
} WindowsInternal;

LRESULT CALLBACK CreateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Window procedure for handling messages
LRESULT CALLBACK CreateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        Window* window = (Window*)pCreate->lpCreateParams;
        SetPropW(hwnd, WINDOW_PROP, (HANDLE)window);
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam); // Add this line
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetPropW(hwnd, WINDOW_PROP);
    printf("Main WNDPROC\n");
    switch (uMsg) {
        case WM_CLOSE:
            if (window) {
                window->ShouldClose = true;
                SKLINFO("Window is closing.");
            }
            PostQuitMessage(0);
            break;
        case WM_DESTROY:
            if (window) {
                window->ShouldClose = true;
                SKLINFO("Window is being destroyed.");
            }
            break;
        // Add more case statements for other messages as needed
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


// Platform-specific window creation function
Window* CreateSklcWindow(int width, int height, const char* title) {
    Window* window = (Window*)malloc(sizeof(Window));
    WindowsInternal* internal = (WindowsInternal*)malloc(sizeof(WindowsInternal));

    internal->hInstance = GetModuleHandle(NULL);

    // Register the window class
    const char* className = "SKLCWindowClass";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = CreateWindowProc;
    wc.hInstance = internal->hInstance;
    wc.lpszClassName = className;
    wc.style = CS_HREDRAW | CS_HREDRAW;

    if (!RegisterClass(&wc)) {
        SKLERROR("Failed to register window class.");
        free(internal);
        free(window);
        return NULL;
    }

    // Create the window
    internal->hwnd = CreateWindowEx(
        0,
        className,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        internal->hInstance,
        window // Pass the window pointer here
    );


    if (internal->hwnd == NULL) {
        SKLERROR("Failed to create window.");
        free(window);
        free(internal);
        return NULL;
    }

    window->internal = internal;
    window->width = width;
    window->height = height;
    window->title = _strdup(title);
    window->ShouldClose = false;

    // Show the window
    ShowWindow(internal->hwnd, SW_SHOW);

    return window;
}

// Platform-specific window destruction function
void DestroySklcWindow(Window* window) {
    if (window) {
        WindowsInternal* internal = (WindowsInternal*)window->internal;
        DestroyWindow(internal->hwnd);
        free(internal);
        free(window->title);
        free(window);
    }
}

// Platform-specific window event processing function
void ProcessSklcWindowMessages() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif // SKLC_PLATFORM_WINDOWS