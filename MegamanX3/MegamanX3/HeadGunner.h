#pragma once
#include "Engine.h"
#include "Camera.h"
#include "HeadGunnerState.h"
#include "HeadGunnerStateHandler.h"
#include <list>

class Entity;

class HeadGunner : public HeadGunnerStateHandler, public Entity
{
public:
	HeadGunner();
	~HeadGunner();

	void Initialize(int width, int height);
	void Update();


	/*void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();*/

	//Entity *GetEntity();
	HeadGunnerStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	HeadGunnerStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	//bool GetAction();
	//void SetAction(bool action);

private:
	HeadGunnerState * currentState;
	HeadGunnerState *standingState, *fireState, *jumpState, *dieState, *damagedState, *fallingState;
	HeadGunnerStateHandler::StateName currentStateName;
	//Entity *entity;
	Camera *camera;
	HeadGunnerStateHandler::StateName preAction;
};

