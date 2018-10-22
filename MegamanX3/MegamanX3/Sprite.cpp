#include "pch.h"
#include "Sprite.h"
#include "Engine.h"
#include "ResourceManager.h"

Sprite::Sprite()
{
	texture = nullptr;
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

void Sprite::Render(D3DXVECTOR3 position, RECT rect)
{
	if (texture) {
		Engine::GetEngine()->GetSpriteHandler()->Draw(texture->GetTexture(), &rect, nullptr, &position, color);
	}
}
