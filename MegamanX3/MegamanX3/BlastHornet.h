#pragma once
#include "Engine.h"
#include "Enemy.h"
#include "BlastHornetStateHandler.h"
#include "BlastHornetState.h"
#include "BlastHornetDrop.h"
#include "BlastHornetFly.h"
#include "BlastHornetPrepare.h"
#include "BlastHornetPrick.h"
#include "BlastHornetReturn.h"
#include "BlastHornetDie.h"

class BlastHornet : public BlastHornetStateHandler, public Enemy
{
public:
	BlastHornet(Player *player);
	~BlastHornet();

	void Initialize();
	void Update();

	BlastHornetStateHandler::StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	BlastHornetStateHandler::MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

	StateName GetPreAction();
	void SetPreAction(StateName action);

	D3DXVECTOR3 GetPlayerPos();
	D3DXVECTOR3 GetPointA();
	D3DXVECTOR3 GetPointB();

private:
	BlastHornetState * currentState;
	BlastHornetState *flyState, *prepareState, *prickState, *dieState, *returnState, *dropState;
	BlastHornetStateHandler::StateName currentStateName;
	BlastHornetStateHandler::StateName preAction;

	D3DXVECTOR3 playerPos;
	D3DXVECTOR3 pointA, pointB;
};