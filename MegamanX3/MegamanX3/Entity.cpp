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
	scale = D3DXVECTOR2(1, 1);
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

void Entity::InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float startFrame, float endFrame, float maxFramesRow, float frameWidth, float frameHeight, float animationSpeed, bool isLooping)
{
	sprite = new AnimatedSprite(framesPerSecond, animationSpeed, isLooping);
	((AnimatedSprite*)sprite)->Initialize(device, textureName, startFrame, endFrame, maxFramesRow, frameWidth, frameHeight);
}

void Entity::Update()
{
	float dt = Timer::GetDeltaTime();

	position += velocity * dt;
	velocity *= 0.96f;

	D3DXVECTOR2 center(position.x + (sprite->GetFrameWidth() / 2), position.y + (sprite->GetFrameHeight() / 2));
	if (reverse) {
		scale.x = -scale.x;
	}
	D3DXMatrixTransformation2D(&transformMatrix, &center, 0.0f, &scale, nullptr, 0.0f, nullptr);

	if (sprite) {
		sprite->Update();
	}

	if (reverse) {
		scale.x = -scale.x;
	}
}

void Entity::Render()
{
	if (sprite) {
		//std::cout << "Render to : " << position.x << ", " << position.y << std::endl;
		std::cout << "Sprite RECT to: " << sprite->left << ", " << sprite->top << std::endl;
		LPD3DXSPRITE spriteHandler = Engine::GetEngine()->GetSpriteHandler();

		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);
		spriteHandler->SetTransform(&transformMatrix);
		sprite->Render(position);
		spriteHandler->SetTransform(&oldMatrix);
	}
}

void Entity::SetSpritePosition(float left, float top)
{
	sprite->top = top;
	sprite->left = left;
}

D3DXVECTOR3 Entity::GetPosition()
{
	return position;
}

RECT Entity::GetBound()
{
	RECT bound;
	bound.left = (long)(position.x - sprite->GetFrameWidth() / 2);
	bound.right = (long)(position.x + sprite->GetFrameWidth() / 2);
	bound.top = (long)(position.y - sprite->GetFrameHeight() / 2);
	bound.bottom = (long)(position.y + sprite->GetFrameHeight() / 2);
	return bound;
}

void Entity::SetScale(float x, float y)
{
	scale.x = x;
	scale.y = y;
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
