#pragma once
#include "CarryArmState.h"

class CarryArmDie : public CarryArmState
{
public:
	CarryArmDie(CarryArmStateHandler *handler, Entity *entity);
	~CarryArmDie();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

