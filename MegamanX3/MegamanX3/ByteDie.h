#pragma once
#include "ByteState.h"
class ByteDie :
	public ByteState
{
public:
	ByteDie(ByteStateHandler *handler, Entity *entity);
	~ByteDie();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

