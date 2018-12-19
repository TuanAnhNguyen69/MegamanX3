#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "HeadGunnerStateHandler.h"
#include "Engine.h"
#include <iostream>

class HeadGunnerState
{
public:
	HeadGunnerState(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	HeadGunnerStateHandler *handler;
	Entity *entity;
};

