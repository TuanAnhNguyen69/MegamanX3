#include "pch.h"
#include "Entity.h"
#include "Timer.h"
#include "AnimatedSprite.h"
#include "Engine.h"
#include "Map.h"
#include <iostream>

Entity::Entity()
{
	position = D3DXVECTOR3(0, 0, 0);
	velocity = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR2(1, 1);
	translation = D3DXVECTOR2(0, 0);
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

	D3DXVECTOR2 center(position.x, position.y);
	if (reverse) {
		scale.x = -scale.x;
	}
	D3DXMatrixTransformation2D(&transformMatrix, &center, 0.0f, &scale, nullptr, 0.0f, &translation);

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
		LPD3DXSPRITE spriteHandler = Engine::GetEngine()->GetSpriteHandler();

		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);
		spriteHandler->SetTransform(&transformMatrix);
		sprite->Render(position);
		spriteHandler->SetTransform(&oldMatrix);
	}
}

D3DXVECTOR3 Entity::GetPosition()
{
	return position;
}

RECT Entity::GetBound()
{
	RECT bound;
	bound.left = position.x - sprite->GetFrameWidth() * scale.x / 2;
	bound.right = bound.left + sprite->GetFrameWidth() * scale.x;
	bound.top = position.y - sprite->GetFrameHeight() * scale.y / 2;
	bound.bottom = bound.top + sprite->GetFrameHeight() * scale.y;
	return bound;
}

D3DXVECTOR3 Entity::GetVelocity()
{
	return velocity;
}

float Entity::GetWidth()
{
	return sprite->GetFrameWidth();
}

float Entity::GetHeight()
{
	return sprite->GetFrameHeight();
}

bool Entity::GetReverse()
{
	return this->reverse;
}

void Entity::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void Entity::SetTranslation(float x, float y)
{
	translation.x = x;
	translation.y = y;
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

void Entity::SetVelocityX(float x)
{
	velocity.x = x;
}

void Entity::SetVelocityY(float y)
{
	velocity.y = y;
}

void Entity::AddVelocityX(float x)
{
	velocity.x += x;
}

void Entity::AddVelocityY(float y)
{
	velocity.y += y;
}

void Entity::AddPosition(float x, float y)
{
	position.x += x;
	position.y += y;
}

void Entity::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
