#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "NotorBangerStateHandler.h"
#include "Engine.h"
#include <iostream>

class NotorBangerState
{
public:
	NotorBangerState(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	NotorBangerStateHandler *handler;
	Entity *entity;
};
