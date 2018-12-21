#pragma once
#include "CarryArmState.h"
#include "time.h"
class CarryArmFlying : public CarryArmState
{
public:
	CarryArmFlying(CarryArmStateHandler *handler, Entity *entity);
	~CarryArmFlying();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	clock_t startState;
};

