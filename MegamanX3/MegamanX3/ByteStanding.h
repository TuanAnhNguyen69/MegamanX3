#pragma once
#include "ByteState.h"
#include <time.h>

class ByteStanding : public ByteState
{
public:
	ByteStanding(ByteStateHandler *handler, Entity *entity);
	~ByteStanding();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	clock_t timeCreated, timeSeen;
};

