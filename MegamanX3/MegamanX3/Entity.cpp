#include "pch.h"
#include "Entity.h"
#include "Timer.h"
#include "AnimatedSprite.h"
#include "Engine.h"
#include <iostream>

Entity::Entity(EntityId entityId)
{
	this->entityId = entityId;
	position = D3DXVECTOR3(0, 0, 0);
	velocity = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR2(1, 1);
	translation = D3DXVECTOR2(0, 0);
	reverse = false;
	sprite = nullptr;
	isRemove = false;
}

Entity::Entity()
{
	position = D3DXVECTOR3(0, 0, 0);
	velocity = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR2(1, 1);
	translation = D3DXVECTOR2(0, 0);
	reverse = false;
	sprite = nullptr;
	isRemove = false;
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
	bound.left = position.x - width / 2;
	bound.right = bound.left + width;
	bound.top = position.y - height / 2;
	bound.bottom = bound.top + height;
	return bound;
}

D3DXVECTOR3 Entity::GetVelocity()
{
	return velocity;
}

float Entity::GetWidth()
{
	return width;
}

float Entity::GetHeight()
{
	return height;
}

bool Entity::GetReverse()
{
	return this->reverse;
}

EntityId Entity::GetEntityId()
{
	return this->entityId;
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

void Entity::SetBound(int width, int height)
{
	this->width = width;
	this->height = height;
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

void Entity::SetPositionX(float x)
{
	position.x = x;
}

void Entity::SetPositionY(float y)
{
	position.y = y;
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

void Entity::SetInitialRect(int left, int top, int right, int bottom)
{
	initialRect.left = left;
	initialRect.right = right;
	initialRect.top = top;
	initialRect.bottom = bottom;
}

RECT Entity::GetInitialRect()
{
	return initialRect;
}

void Entity::AddPosition(float x, float y)
{
	position.x += x;
	position.y += y;
}

void Entity::GoTo(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed)
{
	D3DXVECTOR3 moveVector;

	moveVector = D3DXVECTOR3(desPoint.x - curPoint.x, desPoint.y - curPoint.y, 0);

	float speedVector = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

	this->AddVelocityX(moveVector.x / speedVector * speed);
	this->AddVelocityY(moveVector.y / speedVector * speed);

	if ((((desPoint.x >= curPoint.x) && (this->GetPosition().x >= desPoint.x)) ||
		((desPoint.x <= curPoint.x) && (this->GetPosition().x <= desPoint.x))) &&
		(((desPoint.y >= curPoint.y) && (this->GetPosition().y >= desPoint.y)) ||
		((desPoint.y <= curPoint.y) && (this->GetPosition().y <= desPoint.y)))
		)
	{
		this->SetVelocity(0, 0);
		this->SetPosition(desPoint.x, desPoint.y);
	}
}

void Entity::GoOn(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed)
{
	D3DXVECTOR3 moveVector;

	moveVector = D3DXVECTOR3(desPoint.x - curPoint.x, desPoint.y - curPoint.y, 0);

	float speedVector = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

	this->AddVelocityX(moveVector.x / speedVector * speed);
	this->AddVelocityY(moveVector.y / speedVector * speed);
}

void Entity::SetRemove()
{
	isRemove = true;
}

bool Entity::IsRemove()
{
	return isRemove;
}

void Entity::Reset()
{
}

void Entity::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
