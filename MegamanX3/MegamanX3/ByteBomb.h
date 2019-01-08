#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "Engine.h"

namespace Define
{
	const float BYTEBOMB_SPEED = 250.0f;		//vận tốc
	const float BYTEBOMB_ACCELERATION = 10.0f;	//gia tốc
}

class ByteBomb : public Entity
{
public:
	enum MoveDirection
	{
		Left,
		Right,
	};

	enum CollisionDirection
	{
		CollLeft,
		CollRight,
		None
	};

	ByteBomb();
	~ByteBomb();

	void Initailize(MoveDirection moveDirection);
	void Update();
	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	bool IsHitted();

private:
	AnimatedSprite * sprite;
	MoveDirection moveDirection;
	CollisionDirection collDirection;
	bool isRemove;
	bool isAddWall;
	bool hitted;
};

