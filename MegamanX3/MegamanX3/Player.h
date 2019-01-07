#ifndef _PLAYER_H
#define _PLAYER_H

#include "Engine.h"
#include "PlayerStateHandler.h"
#include "PlayerState.h"
#include "Camera.h"

class Entity;

class Player : public PlayerStateHandler, public Entity
{
public:
	Player();
	~Player();

	void Initialize(LPDIRECT3DDEVICE9 device, Camera *camera);
	void Update();

	//void SetPosition(int x, int y);
	//D3DXVECTOR3 GetPosition();

	//Entity *GetEntity();
	StateName GetCurrentStateName();
	void ChangeState(StateName stateName);
	MoveDirection GetMoveDirection();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnNoCollisionWithBottom();
	int fireCoolDown;
	int bulletCharging;
	bool isJumping;
	void Shoot();
	void ChangeBulletState();
	void Render();
	void AutoMove();
	int GetAutoMovedDistance();
	bool GetMovable();
	void SetMovable(bool movable);
	enum BlockType
	{
		BlockLeft,
		BlockRight,
		None
	};
	BlockType blockType;
private:


	PlayerState *currentState;
	PlayerState *standingState, *runningState, *jumpingState, *fallingState, *damagedState, *slidingState, *climbingState;
	PlayerStateHandler::StateName currentStateName;
	//Entity *entity;
	Camera *camera;
	Entity *chargerSuper;
	Entity *chargerExtreme;
	int bulletDamage;
	bool allowSlide;
	bool movable;
	int autoMovedDistance;

	void OnConveyorCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnDoorCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);


};

#endif