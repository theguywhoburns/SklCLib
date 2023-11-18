#include <Windows.h>

#include <sklc_lib/internal/glad/glad_wgl.h>
#include <sklc_lib/internal/glad/glad.h>

#include <sklc_lib/graphics/opengl/opengl.h>



b8 wgl_initialize_functions();

b8 opengl_initialize(struct renderer_backend* backend, const char* app_name) {
    if(!wgl_initialize_functions()) return false;
    return true;
}

b8 opengl_init_wnd(window wnd) {

    HDC hDC = GetDC(wnd->wnd_handle);

    int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

    int pixelFormat = 0;
	UINT numFormats = 0;
	wglChoosePixelFormatARB(hDC, pixelFormatAttributes, NULL, 1, &pixelFormat, &numFormats);
	
    PIXELFORMATDESCRIPTOR pixelFormatDesc = {0};
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);
	SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc);

	int openGLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

    wnd->wnd_context = wglCreateContextAttribsARB(hDC, 0, openGLAttributes);
	if(wnd->wnd_context == NULL) return false;

    return true;
}

void opengl_make_context_current(window wnd) {
    wglMakeCurrent(GetDC(wnd->wnd_handle), (HGLRC)wnd->wnd_context);
}

void opengl_swap_buffers(window wnd, b8 vsync) {
    wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC(wnd->wnd_handle), WGL_SWAP_MAIN_PLANE);
}

void opengl_shutdown(window wnd) {
    wglDeleteContext(wnd->wnd_context);
}

b8 wgl_initialize_functions() {
    WNDCLASSEX windowClass = {0};
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = DefWindowProcA;
    windowClass.lpszClassName = (LPCSTR)L"SKLCDummyWindow";
    windowClass.cbSize = sizeof(WNDCLASSEX);

    u16 classId = RegisterClassEx(&windowClass);

    HWND dummyWindow = CreateWindowEx(
        0,
        MAKEINTATOM(classId),
        (LPCSTR)L"SKLCDummyWindow",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        windowClass.hInstance,
        0);

    if(!dummyWindow) return false;

    HDC dummyDC = GetDC(dummyWindow);

    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixelFormat = ChoosePixelFormat(dummyDC, &pfd);
    SetPixelFormat(dummyDC, pixelFormat, &pfd);



    HGLRC dummyContext = wglCreateContext(dummyDC);
    if(!dummyContext) return false;

    bool res = wglMakeCurrent(dummyDC, dummyContext);
    if(!res) return false;


    if (!gladLoadWGL(dummyDC))
        return false;
    
    if (!gladLoadGL())
        return false;
    

    wglMakeCurrent(dummyDC, 0);
    wglDeleteContext(dummyContext);
    ReleaseDC(dummyWindow, dummyDC);
    DestroyWindow(dummyWindow);

    return true;
}