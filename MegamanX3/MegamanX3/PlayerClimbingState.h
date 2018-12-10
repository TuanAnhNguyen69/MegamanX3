#pragma once
#include "PlayerState.h"

class PlayerClimbingState : public PlayerState
{
public:
	enum ClimbingType
	{
		ClimbingLeft,
		ClimbingRight,
		None,
	};

	PlayerClimbingState(PlayerStateHandler *handler, Entity *entity);
	~PlayerClimbingState();
	void Load();
	void Update();
	void UpdateInput();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	float acceleratorX;
	float acceleratorY;
	ClimbingType climbingType;
	bool isStanding;
	//bool isLeftOrRightKeyPressed;

	//bool isClimbing;
	//bool isClimbingLeft;
	bool isKeyLeft;
	bool isKeyRight;
};
