#pragma once
#include "CarryArmState.h"

class CarryArmDamaged : public CarryArmState
{
public:
	CarryArmDamaged(CarryArmStateHandler *handler, Entity *entity);
	~CarryArmDamaged();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

