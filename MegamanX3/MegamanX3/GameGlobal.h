#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class GameGlobal
{
public:
	GameGlobal();
	~GameGlobal();

	static void SetCurrentHWND(HWND hWnd);
	static HWND getCurrentHWND();

private:
	static HWND mHwnd;

};

