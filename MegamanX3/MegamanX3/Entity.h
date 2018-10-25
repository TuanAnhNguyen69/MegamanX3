#ifndef _ENTITY_H
#define _ENTITY_H

#include <d3d9.h>
#include "Sprite.h"

class Entity
{
public:
	friend class EntityManager;
	~Entity();

	void InitializeSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float frameWidth, float frameHeight, float top = 0, float left = 0);
	void InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float maxFrames, float maxFramesRow, float frameWidth, float frameHeight, float top = 0, float left = 0, float animationSpeed = 1.0f, bool isLooping = true);

	void Update();
	void Render();

	RECT GetBound();
	void SetPosition(float x = 0.0f, float y = 0.0f);
	void SetVelocity(float x = 0.0f, float y = 0.0f);
	void SetReverse(bool reverse);
private:
	Entity(void);

	D3DXMATRIX transformMatrix;
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	Sprite *sprite;
	bool reverse;
};

#endif