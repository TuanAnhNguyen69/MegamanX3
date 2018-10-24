#include "pch.h"
#include "Entity.h"
#include "Timer.h"
#include "AnimatedSprite.h"
#include "Engine.h"
#include <iostream>

Entity::Entity()
{
	position = D3DXVECTOR3(0, 0, 0);
	velocity = D3DXVECTOR3(0, 0, 0);
	reverse = false;
	sprite = nullptr;
}

Entity::~Entity()
{
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}

void Entity::InitializeSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float frameWidth, float frameHeight, float top, float left)
{
	sprite = new Sprite(frameWidth, frameHeight, top, left);
	sprite->Initialize(device, textureName);
}

void Entity::InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float maxFrames, float maxFramesRow, float frameWidth, float frameHeight, float top, float left, float animationSpeed, bool isLooping)
{
	sprite = new AnimatedSprite(framesPerSecond, animationSpeed, isLooping);
	((AnimatedSprite*)sprite)->Initialize(device, textureName, maxFrames, maxFramesRow, frameWidth, frameHeight, top, left);
}

void Entity::Update()
{
	float dt = Timer::GetDeltaTime();

	position += velocity * dt;
	velocity *= 0.96f;

	D3DXMatrixTranslation(&matrixTranslation, position.x, position.y, 0);

	if (sprite) {
		sprite->Update();
	}
}

void Entity::Render()
{
	if (sprite) {
		LPD3DXSPRITE spriteHandler = Engine::GetEngine()->GetSpriteHandler();

		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);

		D3DXMATRIX newMatrix;
		D3DXVECTOR2 center(position.x + (sprite->GetFrameWidth() / 2), position.y + (sprite->GetFrameHeight() / 2));
		D3DXVECTOR2 scale(1, 1);
		if (reverse) {
			scale.x = -1;
		}
		D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &scale, nullptr, 0.0f, nullptr);
		D3DXMATRIX finalMatrix = newMatrix * oldMatrix;

		spriteHandler->SetTransform(&finalMatrix);
		sprite->Render(position);
		spriteHandler->SetTransform(&oldMatrix);
	}
}

void Entity::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Entity::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Entity::SetReverse(bool reverse)
{
	this->reverse = reverse;
}
