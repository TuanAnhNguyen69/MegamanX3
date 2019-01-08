 #pragma once
#include "Engine.h"
#include "Camera.h"
#include "HelitState.h"
#include "HelitStateHandler.h"
#include "HelitDie.h"
#include "HelitShooting.h"
#include "HelitFlying.h"
#include "Enemy.h"
#include <list>
#include <cmath>

//class Entity;

class Helit : public HelitStateHandler, public Enemy
{
public:
	Helit(Player*player);
	~Helit();

	void Initialize();
	void Update();

	HelitStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	HelitStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	bool GetLeftTarget();
	bool GetAboveTarget();
	bool GetHadShootState();
	void SetHadShootState(bool hadShootState);		

private:
	bool targetIsLeft;
	bool targetIsAbove;
	bool hadShootState;
	
	HelitState * currentState;
	HelitState *flyingState, *shootingState, *dieState;
	HelitStateHandler::StateName currentStateName;
	HelitStateHandler::StateName preAction;
};

