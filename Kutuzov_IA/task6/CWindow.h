#pragma once
#include <Windows.h>


LRESULT CALLBACK WindowProcedure(HWND HWnd, UINT UMsg, WPARAM WParam, LPARAM LParam);

class CWindow
{
public:
	CWindow();
	~CWindow();

	bool ProcessMessages();

private:
	HINSTANCE HInstance;
	HWND HWnd;
};

