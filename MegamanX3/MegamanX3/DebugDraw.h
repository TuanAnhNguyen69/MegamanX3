#pragma once

#include <d3dx9.h>
#include "Camera.h"

class DebugDraw
{
public:
	DebugDraw();
	~DebugDraw();

	void Draw();
	void DrawLine(D3DXVECTOR2 lines[], int count);
	void DrawRect(RECT rect, Camera *camera = nullptr);
	//set do rong cua duong ve, mac dinh = 10
	void SetLineSize(float width);
	void SetColor(D3DCOLOR color);

private:
	LPD3DXLINE lineDraw;
	D3DCOLOR color;
};

