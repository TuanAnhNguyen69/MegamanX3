#ifndef _ENTITY_H
#define _ENTITY_H

#include <d3d9.h>
#include "Sprite.h"

class Entity
{
public:
	~Entity();

	void InitializeSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName);
	void InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float animationSpeed = 1.0f, bool isLooping = true);

	void Update();
	void Render();

	void SetPosition(float x = 0.0f, float y = 0.0f);
	void SetVelocity(float x = 0.0f, float y = 0.0f);
private:
	Entity(void);

	D3DXMATRIX matrixTranslation;
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	Sprite *sprite;
};

#endif