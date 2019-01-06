#pragma once
#include "Engine.h"
#include "Camera.h"
#include "HeadGunnerState.h"
#include "HeadGunnerStateHandler.h"
#include "HeadGunnerDamaged.h"
#include "HeadGunnerDie.h"
#include "HeadGunnerShoot.h"
#include "HeadGunnerShootCanon.h"
#include "HeadGunnerShootRocket.h"
#include "HeadGunnerStanding.h"
#include "Enemy.h"
#include "Player.h"
#include <list>

class Entity;

class HeadGunner : public HeadGunnerStateHandler, public Enemy
{
public:
	HeadGunner(Player * player);
	~HeadGunner();

	void Initialize( bool isLeft);
	void Update();

	HeadGunnerStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	HeadGunnerStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	int GetAmmoCanon();
	void ResetAmmoCanon();
	void SubAmmoCanon();

	bool GetIsLeft();

private:
	bool isLeft;
	HeadGunnerState * currentState;
	HeadGunnerState *standingState, *shootState, *shootRocketState, *shootCanonState, *jumpState, *dieState, *damagedState, *fallingState;
	HeadGunnerStateHandler::StateName currentStateName;
	HeadGunnerStateHandler::StateName preAction;
	int ammoCanon;
};

