#pragma once
#include "Enemy.h"
#include "Entity.h"

namespace Define
{
	const float CANON_MAX_VELOCITY_X = 400.0f;
	const float CANON_MAX_HIGH_VELOCITY_Y = 600.0f;
	const float CANON_MAX_LOW_VELOCITY_Y = 400.0f;
	const float CANON_VELOCITY_X = 20.0f; //vX
	const float CANON_HIGH_VELOCITY_Y = 40.0f; //vY khi bắn cao
	const float CANON_LOW_VELOCITY_Y = 15.0f; //vY khi bắn thấp
}

class Canon : public Entity
{
public:
	Canon();
	~Canon();

	void Update();

	void Initialize(bool isHigh, bool isLeft);

	void OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data);

	bool IsHitted();

private:
	AnimatedSprite * sprite;
	bool isLeft;
	bool isHigh;
	bool hitted;
	float x0;
	float y0;
};

