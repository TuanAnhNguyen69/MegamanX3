#ifndef _PLAYER_STATE_H
#define _PLAYER_STATE_H

#include "Entity.h"
#include "PlayerStateHandler.h"
#include "AnimatedSprite.h"

class PlayerState
{
public:
	PlayerState(PlayerStateHandler *handler, Entity *entity);
	~PlayerState();

	virtual void Load();
	virtual void Update();
	virtual void UpdateInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	AnimatedSprite *sprite;
	PlayerStateHandler *handler;
	Entity *entity;
};

#endif