#ifndef _PLAYER_STATE_H
#define _PLAYER_STATE_H

#include "Entity.h"
#include "PlayerStateHandler.h"
#include "AnimatedSprite.h"

class Player;

class PlayerState
{
public:
	PlayerState(PlayerStateHandler *handler, Player *entity);
	~PlayerState();

	virtual void Load();
	virtual void Update();
	virtual void UpdateInput();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	AnimatedSprite *sprite;
	PlayerStateHandler *handler;
	Player *entity;
};

#endif