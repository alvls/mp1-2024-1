#include "CConsoleRender.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>  

using namespace std;



CConsoleRender::CConsoleRender(CGame* InGame): CGameRender(InGame)
{
}

CConsoleRender::~CConsoleRender()
{
}

void CConsoleRender::RenderFrame()
{
	system("CLS");

	for (int y = 0; y < Res_Y; y++)
	{
		string Line;
		for (int x = 0; x < Res_X; x++)
			Line += "#";

		cout << Line << endl;

		
	}

	Sleep(100);
}