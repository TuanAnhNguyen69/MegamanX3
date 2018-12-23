#ifndef _PLAYER_JUMPING_STATE_H
#define _PLAYER_JUMPING_STATE_H

#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	PlayerJumpingState(PlayerStateHandler *handler, Player *entity);
	~PlayerJumpingState();

	void Load();
	void Update();
	void UpdateInput(); 
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	float acceleratorX;
	float acceleratorY;
	bool noPressed;
	AnimatedSprite *jumpSprite;
	AnimatedSprite *fireSprite;
	AnimatedSprite *climbingJumpSprite;
	AnimatedSprite *climbingFireSprite;
};

#endif