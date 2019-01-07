#pragma once
#include "CargoShipState.h"
class CargoShipUpState :
	public CargoShipState
{
public:
	CargoShipUpState(CargoShipStateHandler *handler, Entity *entity);
	~CargoShipUpState();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

