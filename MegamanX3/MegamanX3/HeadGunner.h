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
	HeadGunner(float positionX, float positionY, float scaleX, float scaleY);
	~HeadGunner();

	void Initialize();
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

