#pragma once
#include "ByteState.h"


class ByteThrow :
	public ByteState
{
public:
	ByteThrow(ByteStateHandler *handler, Entity *entity);
	~ByteThrow();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	bool hadThrow;
};

