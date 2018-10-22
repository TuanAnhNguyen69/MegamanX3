#include "pch.h"
#include "FrameWork.h"
#include "SystemDefs.h"
#include "Timer.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

FrameWork::FrameWork()
{
}

FrameWork::~FrameWork()
{
	if (FULL_SCREEN) {
		ChangeDisplaySettings(nullptr, 0);
	}
	Engine::GetEngine()->Release();
	UnregisterClass(applicationName, instance);
	instance = nullptr;
}

bool FrameWork::Initialize() {
	if (!CreateDxWindow((char *)"Megaman", WINDOW_POSX, WINDOW_POSY, SCREEN_WIDTH, SCREEN_HEIGHT)) {
		return false;
	}
	if (!Engine::GetEngine()->Initialize(instance, Engine::GetEngine()->GetGraphics()->GetHwnd())) {
		return false;
	}
	return true;
}

void FrameWork::Run() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Timer::Update();
			Engine::GetEngine()->Run();
		}
	}
}


bool FrameWork::CreateDxWindow(char* windowTitle, int x, int y, int width, int height) {
	HWND hwnd;
	WNDCLASSEX wc;

	applicationName = windowTitle;

	instance = GetModuleHandle(nullptr);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, "RegisterClassEx() failed", "Error", MB_OK);
		return false;
	}

	int style = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN) {
		DEVMODE dmScreenSetting;
		memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
		dmScreenSetting.dmSize = sizeof(dmScreenSetting);
		dmScreenSetting.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSetting.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSetting.dmBitsPerPel = 32;
		dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		
		ChangeDisplaySettings(&dmScreenSetting, CDS_FULLSCREEN);
	}
	else {
		screenHeight = height;
		screenWidth = width;
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowTitle, windowTitle, style, x, y, screenWidth, screenHeight, nullptr, nullptr, instance, nullptr);

	if (hwnd == nullptr) {
		MessageBox(nullptr, "CreateWindowEx() failed", "Error", MB_OK);
		Engine::GetEngine()->Release();
		PostQuitMessage(0);

		return false;
	}

	if (!Engine::GetEngine()->InitializeGraphics(hwnd)) {
		MessageBox(hwnd, "Could not initialize DirectX11", "Error", MB_OK);
		Engine::GetEngine()->Release();
		PostQuitMessage(0);
		UnregisterClass(applicationName, instance);
		instance = nullptr;
		DestroyWindow(hwnd);

		return false;
	}

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return true;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		DestroyWindow(hwnd);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}