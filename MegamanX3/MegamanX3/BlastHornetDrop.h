#pragma once
#include "BlastHornetState.h"
class BlastHornetDrop :
	public BlastHornetState
{
public:
	BlastHornetDrop(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetDrop();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

