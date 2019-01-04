#pragma once
#include "Entity.h"
#include "Engine.h"

namespace Define
{
	const float CONVEYOR_SPEED = 15.0f;
}

class Conveyor : public Entity
{
public:
	Conveyor(EntityId id);
	~Conveyor();

	void Update();

	void Initialize();

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	float GetSpeed();

private:
	float speed;
	AnimatedSprite * sprite;
};

