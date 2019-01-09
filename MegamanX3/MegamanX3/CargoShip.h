#pragma once
#include "Engine.h"
#include "Camera.h"
#include "Enemy.h"
#include "CargoShipDownState.h"
#include "CargoShipUpState.h"
#include "CargoShipDropState.h"
#include "CargoShipStateHandler.h"
#include "Sound.h"

class Entity;

class CargoShip : public CargoShipStateHandler, public Enemy
{
public:
	CargoShip(Player *player);
	~CargoShip();

	void Initialize(Camera *camera);
	void Update();

	CargoShipStateHandler::StateName GetCurrentStateName();
	void ChangeState(CargoShipStateHandler::StateName state);
	//void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	D3DXVECTOR3 GetOriginalSolePos();
	void SetRemoveSole();
	void SetRemove();
	void Render();

private:
	CargoShipState * currentState, *downState, *upState, *dropState;
	CargoShipStateHandler::StateName currentStateName;
	Camera *camera;
	D3DXVECTOR3 originalSolePos;
	bool remove;
};

