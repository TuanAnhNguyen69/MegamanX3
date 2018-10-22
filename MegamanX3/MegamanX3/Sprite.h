#ifndef _SPRITE_H
#define _SPRITE_H

#include <d3dx9.h>
#include "Texture.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	virtual void Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName);
	virtual void Update() {}
	virtual void Render(D3DXVECTOR3 position, RECT rect);

private: 
	Texture *texture;
	D3DXCOLOR color;
};

#endif