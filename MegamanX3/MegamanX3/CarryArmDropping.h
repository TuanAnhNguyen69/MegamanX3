#pragma once
#include "CarryArmState.h"

class CarryArmDropping : public CarryArmState
{
public:
	CarryArmDropping(CarryArmStateHandler *handler, Entity *entity);
	~CarryArmDropping();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

