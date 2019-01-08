#pragma once
#include "Engine.h"
#include "Camera.h"
#include "CarryArmState.h"
#include "CarryArmStateHandler.h"
#include "CarryArmDie.h"
#include "CarryArmDropping.h"
#include "CarryArmFlying.h"
#include "Enemy.h"
#include <list>
#include <cmath>
#include "Box.h"

class Entity;

class CarryArm : public CarryArmStateHandler, public Enemy
{
public:
	CarryArm(Player*player);
	~CarryArm();

	void Initialize();
	void Update();

	CarryArmStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	CarryArmStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	bool GetLeftTarget();
	bool GetAboveTarget();
	bool GetHadDropState();
	void SetHadDropState(bool hadDropState);
	

private:
	bool targetIsLeft;
	bool targetIsAbove;
	bool hadDropState;
	CarryArmState * currentState;
	CarryArmState *flyingState, *droppingState, *dieState;
	CarryArmStateHandler::StateName currentStateName;

	CarryArmStateHandler::StateName preAction;
};

