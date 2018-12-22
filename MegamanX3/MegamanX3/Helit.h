#pragma once
#include "Engine.h"
#include "Camera.h"
#include "HelitState.h"
#include "HelitStateHandler.h"
#include "HelitDamaged.h"
#include "HelitDie.h"
#include "HelitShooting.h"
#include "HelitFlying.h"
#include "Enemy.h"
#include <list>
#include <cmath>

class Entity;

using namespace std;

class Helit : public HelitStateHandler, public Enemy
{
public:
	Helit(Player*player);
	~Helit();

	void Initialize();
	void Update();


	/*void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();*/

	//Entity *GetEntity();
	HelitStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	HelitStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	//bool GetAction();
	//void SetAction(bool action);
	bool GetLeftTarget();
	bool GetAboveTarget();
	bool GetHadShootState();
	void SetHadShootState(bool hadShootState);
	

private:
	bool targetIsLeft;
	bool targetIsAbove;
	bool hadShootState;
	HelitState * currentState;
	HelitState *flyingState, *shootingState, *dieState, *damagedState;
	HelitStateHandler::StateName currentStateName;
	//Entity *entity;
	Camera *camera;
	HelitStateHandler::StateName preAction;
};

