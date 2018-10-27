#ifndef _PLAYER_H
#define _PLAYER_H

#include "Engine.h"
#include "PlayerStateHandler.h"
#include "PlayerState.h"

class Entity;

class Player : public PlayerStateHandler
{
public:
	Player();
	~Player();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();

	void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();

	StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	MoveDirection GetMoveDirection();

private:
	PlayerState *currentState;
	PlayerState *standingState, *runningState;
	PlayerStateHandler::StateName currentStateName;
	void UpdateInput();
	Entity *entity;
};

#endif