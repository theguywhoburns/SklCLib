#include <sklc_lib/defines.h>
#include <sklc_lib/graphics/window.h>

#define GetHInstance() GetModuleHandle(NULL)

LRESULT CALLBACK WindowProcessHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	switch (message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
	}break;
	
	default:
		break;
	}
	
	return DefWindowProc(hwnd, message, wparam, lparam);
}

window window_create(
    const char* window_name,
    int width,
    int height,
    int x,
    int y) {

	window ret = malloc(sizeof(struct window));
	ret->window_name = malloc((string_strlen(window_name) + 1) * sizeof(wchar));

	wcscpy_s(ret->window_name, string_strlen(window_name) + 1, (wchar*)TEXT(window_name));
	ret->width = width;
	ret->height = height;
	ret->x = x;
	ret->y = y;

	/* - Create Window Class - */

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = __SKLC_WNDCLASSNAME;

	wcex.lpszMenuName = NULL;

	wcex.hInstance = GetHInstance();

	wcex.lpfnWndProc = WindowProcessHandler;

	ret->wcex = wcex;

	RegisterClassExW(&ret->wcex);

	/* - Create and Display our Window  - */

	ret->wnd_handle = CreateWindowW(__SKLC_WNDCLASSNAME, ret->window_name, WS_OVERLAPPEDWINDOW,
		ret->x, ret->y, ret->width, ret->height, NULL, NULL, GetHInstance(), NULL);
	if (!ret->wnd_handle) {
		MessageBoxW(0, L"Failed to Create Window!.", 0, 0);
		return 0; 
	}


	ShowWindow(ret->wnd_handle, SW_SHOW);
	
	ret->is_running = true;

	return ret;
}

bool window_update(window wnd) {
	MSG msg = { 0 };
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
	if(msg.message == WM_QUIT) wnd->is_running = false;
	return wnd->is_running;
}

void window_destroy(window wnd) {
	free(wnd->window_name);
	free(wnd);
}