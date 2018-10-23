#include "pch.h"
#include "Sprite.h"
#include "Engine.h"
#include "ResourceManager.h"
#include <iostream>

Sprite::Sprite() {
	texture = nullptr;
	color = D3DCOLOR_XRGB(255, 255, 255);
}

Sprite::Sprite(float frameWidth, float frameHeight, float top, float left)
{
	texture = nullptr;
	this->top = top;
	this->left = left;
	this->frameHeight = frameHeight;
	this->frameWidth = frameWidth;
	color = D3DCOLOR_XRGB(255, 255, 255);
}

Sprite::~Sprite()
{
}

void Sprite::Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName)
{
	if (textureName != nullptr) {
		texture = ResourceManager::GetInstance()->GetTextureByName((char*)textureName);
	}
}

void Sprite::Render(D3DXVECTOR3 position)
{
	if (texture) {
		RECT rect;
		rect.top = (long)top;
		rect.left = (long)left;
		rect.bottom = (long)(rect.top + frameHeight);
		rect.right = (long)(rect.left + frameWidth);
		Engine::GetEngine()->GetSpriteHandler()->Draw(texture->GetTexture(), &rect, nullptr, &position, color);
	}
}
