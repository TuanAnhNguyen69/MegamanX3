#pragma once
#include "Engine.h"
#include "Camera.h"
#include "NotorBangerState.h"
#include "NotorBangerStateHandler.h"
#include <list>

class Entity;

class NotorBanger : public NotorBangerStateHandler, public Entity
{
public:
	NotorBanger(float positionX, float positionY, float scaleX, float scaleY);
	~NotorBanger();

	void Initialize();
	void Update();
	

	/*void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();*/

	//Entity *GetEntity();
	NotorBangerStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	NotorBangerStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	bool GetAction();
	void SetAction(bool action);

private:
	NotorBangerState * currentState;
	NotorBangerState *standingState, *fireState, *jumpState, *dieState, *damagedState, *fallingState;
	NotorBangerStateHandler::StateName currentStateName;
	//Entity *entity;
	Camera *camera;
	NotorBangerStateHandler::StateName preAction;
};

