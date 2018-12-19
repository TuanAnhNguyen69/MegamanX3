#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "Engine.h"
#include "ByteStateHandler.h"
#include "ByteBomb.h"

class ByteState
{
public:
	ByteState(ByteStateHandler *handler, Entity *entity);
	~ByteState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	ByteStateHandler *handler;
	Entity *entity;

};

