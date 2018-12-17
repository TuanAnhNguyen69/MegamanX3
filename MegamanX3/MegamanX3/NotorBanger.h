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
#include <list>

class Entity;

class NotorBanger : public NotorBangerStateHandler, public Entity
{
public:
	NotorBanger();
	~NotorBanger();

	void Initialize();
	void Update();

	NotorBangerStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	NotorBangerStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	StateName GetPreAction();
	void SetPreAction(StateName action);

	void SetBarrelState(BarrelState bt);
	BarrelState GetBarrelState();

private:
	NotorBangerState * currentState;
	NotorBangerState *standingState, *shootState, *jumpState, *dieState, *damagedState, *fallingState, *changeBarrel;
	NotorBangerStateHandler::StateName currentStateName;
	Camera *camera;
	NotorBangerStateHandler::StateName preAction;
	BarrelState barrelState;
};

