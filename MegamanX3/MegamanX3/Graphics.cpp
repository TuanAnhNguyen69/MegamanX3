#include "pch.h"
#include "Graphics.h"


Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	if (dxManager) {
		delete dxManager;
		dxManager = nullptr;
	}
}

bool Graphics::InitializeDX()
{
	dxManager = new DXManager();
	if (!dxManager->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, hwnd, FULL_SCREEN)) {
		return false;
	}
	return true;
}

bool Graphics::Initialize()
{
	return true;
}

void Graphics::BeginScene(D3DCOLOR color)
{
	dxManager->BeginScene(color);
}

void Graphics::EndScene()
{
	dxManager->EndScene();
}

DXManager * Graphics::GetDXManager()
{
	return dxManager;
}

HWND Graphics::GetHwnd()
{
	return hwnd;
}

void Graphics::SetHwnd(HWND hwnd)
{
	this->hwnd = hwnd;
}

LPDIRECT3DDEVICE9 Graphics::GetDevice()
{
	return dxManager->device;
}
