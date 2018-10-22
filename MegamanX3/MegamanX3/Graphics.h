#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "DXManager.h"
#include "SystemDefs.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool InitializeDX();
	bool Initialize();
	void BeginScene(D3DCOLOR color);
	void EndScene();

	DXManager *GetDXManager();
	HWND GetHwnd();

	void SetHwnd(HWND hwnd);
	LPDIRECT3DDEVICE9 GetDevice();

private:
	DXManager *dxManager;
	HWND hwnd;
};

#endif