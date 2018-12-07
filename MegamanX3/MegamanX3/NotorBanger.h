#pragma once
#include "Engine.h"
#include "Camera.h"
#include "NotorBangerState.h"
#include "NotorBangerStateHandler.h"
#include <list>

class Entity;

class NotorBanger : NotorBangerStateHandler
{
public:
	NotorBanger();
	~NotorBanger();

	void Initialize(LPDIRECT3DDEVICE9 device, Camera *camera);
	void Update();
	

	void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();

	Entity *GetEntity();
	NotorBangerStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	NotorBangerStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

private:
	NotorBangerState * currentState;
	NotorBangerState *standingState, *fireState, *jumpState, *dieState, *damagedState;
	NotorBangerStateHandler::StateName currentStateName;
	Entity *entity;
	Camera *camera;
};

