#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "CarryArmStateHandler.h"
#include "Engine.h"
#include <iostream>

class CarryArmState
{
public:
	CarryArmState(CarryArmStateHandler *handler, Entity *entity);
	~CarryArmState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	CarryArmStateHandler *handler;
	Entity *entity;
	/*bool hadShootState;*/
};

