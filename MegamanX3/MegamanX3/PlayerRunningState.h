#ifndef _PLAYER_RUNNING_STATE_H
#define _PLAYER_RUNNING_STATE_H

#include "PlayerState.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(PlayerStateHandler *handler, Entity *entity);
	~PlayerRunningState();

	void Load();
	void Update();
	void UpdateInput(); 
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	float acceleratorX;
};

#endif