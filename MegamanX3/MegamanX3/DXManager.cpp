#include "pch.h"
#include "DXManager.h"

DXManager::DXManager()
{
}

DXManager::~DXManager()
{
	if (device) {
		device->Release();
		device = nullptr;
	}

	if (direct3d) {
		direct3d->Release();
		direct3d = nullptr;
	}
}

bool DXManager::Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullscreen)
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == nullptr) {
		return false;
	}

	D3DPRESENT_PARAMETERS presentationParam;
	ZeroMemory(&presentationParam, sizeof(presentationParam));
	presentationParam.Windowed = !fullscreen;
	presentationParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentationParam.hDeviceWindow = hwnd;

	HRESULT result = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParam, &device);
	if (FAILED(result)) {		
		return false;
	}
	return true;
}

void DXManager::BeginScene(D3DCOLOR color)
{
	device->Clear(0, nullptr, D3DCLEAR_TARGET, color, 1.0f, 0);
	device->BeginScene();
}

void DXManager::EndScene() {
	device->EndScene();
	device->Present(nullptr, nullptr, nullptr, nullptr);
}
