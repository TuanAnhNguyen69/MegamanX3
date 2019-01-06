#pragma once
#include "Engine.h"
#include "Camera.h"
#include "NotorBangerState.h"
#include "NotorBangerStateHandler.h"
#include "NotorBangerDamaged.h"
#include "NotorBangerDie.h"
#include "NotorBangerJump.h"
#include "NotorBangerShoot.h"
#include "NotorBangerStanding.h"
#include "NotorBangerChangeBarrel.h"
#include "Enemy.h"
#include <list>

class Entity;

class NotorBanger : public NotorBangerStateHandler, public Enemy
{
public:
	NotorBanger(Player *player);
	~NotorBanger();

	void Initialize();
	void Update();

	NotorBangerStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	NotorBangerStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	StateName GetPreAction();
	void SetPreAction(StateName action);

	void SetBarrelState(BarrelState bt);
	BarrelState GetBarrelState();

	bool GetLeftTarget();
	bool GetAboveTarget();

	D3DXVECTOR3 GetPlayerPos();
	bool HadChangeHigh();
	void SetHadChangeHigh(bool hadChangeHigh);

private:
	NotorBangerState * currentState;
	NotorBangerState *standingState, *shootState, *jumpState, *dieState, *damagedState, *fallingState, *changeBarrelState;
	NotorBangerStateHandler::StateName currentStateName;
	NotorBangerStateHandler::StateName preAction;
	BarrelState barrelState;
	

};

