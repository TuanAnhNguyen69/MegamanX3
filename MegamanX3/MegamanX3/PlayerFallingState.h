#ifndef _PLAYER_FALLING_STATE_H
#define _PLAYER_FALLING_STATE_H

#include "PlayerState.h"

class PlayerFallingState : public PlayerState
{
public:
	PlayerFallingState(PlayerStateHandler *handler, Entity *entity);
	~PlayerFallingState();

	void Load();
	void Update();
	void UpdateInput();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	float acceleratorX;
	float acceleratorY;
	bool isLeftOrRightKeyPressed;
};

#endif