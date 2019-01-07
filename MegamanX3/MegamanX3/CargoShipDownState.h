#pragma once
#include "CargoShipState.h"
class CargoShipDownState :
	public CargoShipState
{
public:
	CargoShipDownState(CargoShipStateHandler *handler, Entity *entity);
	~CargoShipDownState();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	D3DXVECTOR3 startPos, desPos;
};

