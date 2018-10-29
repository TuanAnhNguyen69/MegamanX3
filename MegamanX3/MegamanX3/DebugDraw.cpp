#include "pch.h"
#include "DebugDraw.h"
#include "Engine.h"

DebugDraw::DebugDraw()
{
	D3DXCreateLine(Engine::GetEngine()->GetGraphics()->GetDevice(), &lineDraw);

	//set size cho line
	lineDraw->SetWidth(5);

	//set mau cho line
	color = D3DCOLOR_XRGB(255, 0, 0);
}


DebugDraw::~DebugDraw()
{
}

void DebugDraw::Draw()
{
}

void DebugDraw::DrawLine(D3DXVECTOR2 lines[], int count)
{
	lineDraw->Begin();
	lineDraw->Draw(lines, count, color);
	lineDraw->End();
}

void DebugDraw::DrawRect(RECT rect, Camera * camera)
{
	D3DXVECTOR3 trans = D3DXVECTOR3(0, 0, 0);

	if (camera)
	{
		trans = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0) - camera->GetCenter();
	}

	D3DXVECTOR2 lines[] = { D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y),
							D3DXVECTOR2(rect.right + trans.x, rect.top + trans.y),
							D3DXVECTOR2(rect.right + trans.x, rect.bottom + trans.y),
							D3DXVECTOR2(rect.left + trans.x, rect.bottom + trans.y),
							D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y) };

	DrawLine(lines, 5);
}

void DebugDraw::SetLineSize(float width)
{
	lineDraw->SetWidth(width);
}

void DebugDraw::SetColor(D3DCOLOR color)
{
	this->color = color;
}
