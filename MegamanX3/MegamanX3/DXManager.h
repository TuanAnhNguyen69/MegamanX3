#ifndef _DX_MANAGER_H
#define _DX_MANAGER_H

#include <d3d9.h>

class DXManager
{
public:
	DXManager();
	~DXManager();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullscreen);
	void BeginScene(D3DCOLOR color);
	void EndScene();

	LPDIRECT3DDEVICE9 device;
private:
	LPDIRECT3D9 direct3d;

	
};

#endif