#pragma once
#include "Engine.h"
#include "Camera.h"
#include "Enemy.h"
#include "ShurikenState.h"
#include "ShurikenAttack1.h"
#include "ShurikenAttack2.h"
#include "ShurikenDie.h"
#include "ShurikenJump.h"
#include "ShurikenFlip.h"
#include "ShurikenTurn.h"

class Shuriken : public ShurikenStateHandler, public Enemy
{
public:
	Shuriken(Player *player);
	~Shuriken();

	void Initialize();
	void Update();

	ShurikenStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	ShurikenStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	StateName GetPreAction();
	void SetPreAction(StateName action);

	bool GetLeftTarget();
	bool GetAboveTarget();

	Player *player;
private:
	ShurikenState * currentState;
	ShurikenState *turnState, *attack1State, *attack2State, *jumpState, *dieState, *flipState, *moveState;
	ShurikenStateHandler::StateName currentStateName;
	ShurikenStateHandler::StateName preAction;
	bool targetIsLeft;
	bool targetIsAbout;
};
