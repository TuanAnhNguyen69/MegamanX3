#pragma once
#include "Engine.h"
#include "Camera.h"
#include "CarryArmState.h"
#include "CarryArmStateHandler.h"
#include "CarryArmDamaged.h"
#include "CarryArmDie.h"
#include "CarryArmDropping.h"
#include "CarryArmFlying.h"
#include "Enemy.h"
#include <list>
#include <cmath>
#include "Box.h"

class Entity;

using namespace std;

class CarryArm : public CarryArmStateHandler, public Enemy
{
public:
	CarryArm(Player*player);
	~CarryArm();

	void Initialize();
	void Update();


	/*void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();*/

	//Entity *GetEntity();
	CarryArmStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	CarryArmStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	//bool GetAction();
	//void SetAction(bool action);
	bool GetLeftTarget();
	bool GetAboveTarget();
	bool GetHadDropState();
	void SetHadDropState(bool hadDropState);
	

private:
	bool targetIsLeft;
	bool targetIsAbove;
	bool hadDropState;
	CarryArmState * currentState;
	CarryArmState *flyingState, *droppingState, *dieState, *damagedState;
	CarryArmStateHandler::StateName currentStateName;
	//Entity *entity;
	Camera *camera;
	CarryArmStateHandler::StateName preAction;

	//Box *box;
};

