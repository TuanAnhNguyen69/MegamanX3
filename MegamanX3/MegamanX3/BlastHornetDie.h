#pragma once
#include "BlastHornetState.h"
class BlastHornetDie :
	public BlastHornetState
{
public:
	BlastHornetDie(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetDie();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

