#include "pch.h"
#include "Entity.h"
#include "Timer.h"
#include "AnimatedSprite.h"

Entity::Entity()
{
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
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

void Entity::InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float maxFramesRow, float frameWidth, float frameHeight, float top, float left, float animationSpeed, bool isLooping)
{
	sprite = new AnimatedSprite(framesPerSecond, animationSpeed, isLooping);
	((AnimatedSprite*)sprite)->Initialize(device, textureName, maxFramesRow, frameWidth, frameHeight, top, left);
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
