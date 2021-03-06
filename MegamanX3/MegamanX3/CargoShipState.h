#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "CargoShipStateHandler.h"
#include "Engine.h"
#include <iostream>
#include <time.h>
#include "Sound.h"

class CargoShipState
{
public:
	CargoShipState(CargoShipStateHandler *handler, Entity *entity);
	~CargoShipState();
	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	CargoShipStateHandler *handler;
	Entity *entity;

	clock_t timeStartState, timeCount;
};

