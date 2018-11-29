#ifndef _ENEMY_STATE_H
#define _ENEMY_STATE_H

#include "Entity.h"
#include "BlastHornetStateHandler.h"
#include "AnimatedSprite.h"

class BlastHornetState
{
public:
	BlastHornetState(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	AnimatedSprite *sprite;
	BlastHornetStateHandler *handler;
	Entity *entity;
};

#endif