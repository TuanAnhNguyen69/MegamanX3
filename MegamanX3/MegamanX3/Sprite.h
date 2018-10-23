#ifndef _SPRITE_H
#define _SPRITE_H

#include <d3dx9.h>
#include "Texture.h"

class Sprite
{
public:
	Sprite();
	Sprite(float frameWidth, float frameHeight, float top = 0, float left = 0);
	virtual ~Sprite();

	virtual void Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName);
	virtual void Update() {}
	virtual void Render(D3DXVECTOR3 position);

protected:
	float frameHeight;
	float frameWidth;
	float top;
	float left;

private: 
	Texture *texture;
	D3DXCOLOR color;
};

#endif