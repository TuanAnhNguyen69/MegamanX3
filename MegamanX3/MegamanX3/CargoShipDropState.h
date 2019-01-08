#pragma once
#include "CargoShipState.h"
#include "CarryArm.h"

class CargoShipDropState :
	public CargoShipState
{
public:
	CargoShipDropState(CargoShipStateHandler *handler, Entity *entity);
	~CargoShipDropState();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	bool hadDrop, done, dropLeft;
	int countCarryArm, originalCountCarryArm;

	clock_t timeStartUp, timeCountAfterDrop;
};

