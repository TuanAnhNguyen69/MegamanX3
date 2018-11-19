#ifndef _PLAYER_H
#define _PLAYER_H

#include "Engine.h"
#include "PlayerStateHandler.h"
#include "PlayerState.h"
#include "Camera.h"

class Entity;

class Player : public PlayerStateHandler
{
public:
	Player();
	~Player();

	void Initialize(LPDIRECT3DDEVICE9 device, Camera *camera);
	void Update();

	void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();

	Entity *GetEntity();
	StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();

private:
	PlayerState *currentState;
	PlayerState *standingState, *runningState, *jumpingState, *fallingState, *damagedState, *slidingState;
	PlayerStateHandler::StateName currentStateName;
	Entity *entity;
	Camera *camera;
	bool allowJump;
};

#endif