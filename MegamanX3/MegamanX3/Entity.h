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
	void InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float startFrame, float endFrame, float maxFramesRow, float frameWidth, float frameHeight, float animationSpeed = 1.0f, bool isLooping = true);

	void Update();
	void Render();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();
	D3DXVECTOR3 GetVelocity();

	void SetSprite(Sprite *sprite);
	void SetScale(float x = 1.0f, float y = 1.0f);
	void SetPosition(float x = 0.0f, float y = 0.0f);
	void SetVelocity(float x = 0.0f, float y = 0.0f);
	void SetReverse(bool reverse);

	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void AddVelocityX(float x);
	void AddVelocityY(float y);
private:
	Entity(void);

	D3DXMATRIX transformMatrix;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	Sprite *sprite;
	bool reverse;
};

#endif