#include "pch.h"
#include "GameGlobal.h"

HWND GameGlobal::mHwnd = NULL;

GameGlobal::GameGlobal()
{
}


GameGlobal::~GameGlobal()
{
}

void GameGlobal::SetCurrentHWND(HWND hWnd)
{
	mHwnd = hWnd;
}

HWND GameGlobal::getCurrentHWND()
{
	return mHwnd;
}
