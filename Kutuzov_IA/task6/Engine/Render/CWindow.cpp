#include "CWindow.h"
#include <Windows.h>

#include <GL/GL.h>
#pragma comment (lib, "opengl32.lib")

using namespace std;


LRESULT CALLBACK WindowProcedure(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch (UMsg)
	{
	case WM_CLOSE:
		DestroyWindow(HWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(HWnd, UMsg, WParam, LParam);
}

CWindow::CWindow(std::string Title, int Width, int Height) : HInstance(GetModuleHandle(nullptr))
{
	char ClassName[28] = "Scarlet Engine Window Class";

	WNDCLASS WndClass = {};
	WndClass.lpszClassName = ClassName;
	WndClass.hInstance = HInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.lpfnWndProc = WindowProcedure;

	RegisterClass(&WndClass);

	DWORD Style = WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU | CS_OWNDC;

	RECT Rect;
	Rect.left = 250;
	Rect.top = 250;
	Rect.right = Rect.left + Width;
	Rect.bottom = Rect.top + Height;

	AdjustWindowRect(&Rect, Style, false);

	HWnd = CreateWindowEx(
		0,
		ClassName,
		Title.c_str(),
		Style,
		Rect.left,
		Rect.top,
		Rect.right - Rect.left,
		Rect.bottom - Rect.top,
		NULL,
		NULL,
		HInstance,
		NULL
	);

	// Context Creation

	PIXELFORMATDESCRIPTOR Pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};


	int PixelFormatNumber = ChoosePixelFormat(GetDC(HWnd), &Pfd);
	SetPixelFormat(GetDC(HWnd), PixelFormatNumber, &Pfd);
	
	HGLRC HGLRContext = wglCreateContext(GetDC(HWnd));
	//wglGetProcAddress()

	wglMakeCurrent(GetDC(HWnd), HGLRContext);


	ShowWindow(HWnd, SW_SHOW);
}

CWindow::~CWindow()
{
	char ClassName[28] = "Scarlet Engine Window Class";

	UnregisterClass(ClassName, HInstance);
}

bool CWindow::ProcessMessages()
{
	MSG Msg = {};

	while (PeekMessage(&Msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (Msg.message == WM_QUIT)
			return false;

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return true;
}

