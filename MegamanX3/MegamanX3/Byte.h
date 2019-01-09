#pragma once
#include "Enemy.h"
#include "Energy.h"
#include "ByteStateHandler.h"
#include "ByteState.h"
#include "ByteStanding.h"
#include "ByteAttack.h"
#include "ByteThrow.h"
#include "ByteDie.h"

class Entity;

class Byte : public ByteStateHandler, public Enemy
{
public:
	Byte(Player *player);
	~Byte();

	void Initialize();

	void Update();

	ByteStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	ByteStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	StateName GetPreAction();
	void SetPreAction(StateName action);

	bool IsFaceLeft();
	void SetFace(bool isLeft);

	void Seen();
	bool GetSeen();

private:
	ByteState *currentState;
	ByteState *standingState, *attackState, *throwState, *dieState;
	ByteStateHandler::StateName currentStateName, preAction;
	bool seen;
	bool dead;
};

