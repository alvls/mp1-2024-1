#pragma once
#include <Windows.h>
#include <string>


LRESULT CALLBACK WindowProcedure(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

class CWindow
{
public:
	CWindow(std::string Title, int Width = 1920, int Height = 1080);
	~CWindow();

	bool ProcessMessages();

private:
	HINSTANCE HInstance;
	HWND HWnd;
};

