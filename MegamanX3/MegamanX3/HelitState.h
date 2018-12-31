#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "HelitStateHandler.h"
#include "Engine.h"
#include <iostream>

class HelitState
{
public:
	HelitState(HelitStateHandler *handler, Entity *entity);
	~HelitState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	HelitStateHandler *handler;
	Entity *entity;
	/*bool hadShootState;*/
};

