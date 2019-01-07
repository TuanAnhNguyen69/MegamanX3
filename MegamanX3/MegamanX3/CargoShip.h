#pragma once
#include "Engine.h"
#include "Camera.h"
#include "Enemy.h"
#include "CargoShipDownState.h"
#include "CargoShipUpState.h"
#include "CargoShipDropState.h"
#include "CargoShipStateHandler.h"
class CargoShip : public CargoShipStateHandler, public Enemy
{
public:
	CargoShip(Player *player);
	~CargoShip();

	void Initialize();
	void Update();

	CargoShipStateHandler::StateName GetCurrentStateName();
	void ChangeState(CargoShipStateHandler::StateName state);
	//void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	CargoShipState * currentState, *downState, *upState, *dropState;
	CargoShipStateHandler::StateName currentStateName;
};

