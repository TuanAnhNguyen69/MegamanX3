#ifndef _PLAYER_RUNNING_STATE_H
#define _PLAYER_RUNNING_STATE_H

#include "PlayerState.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(PlayerStateHandler *handler, Player *entity);
	~PlayerRunningState();

	void Load();
	void Update();
	void UpdateInput(); 
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	float acceleratorX;
	void OnPlatformCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnRoofCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnUpPlatformCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnDownPlatformCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnConveyorCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

#endif