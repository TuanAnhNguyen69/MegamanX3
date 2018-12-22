#pragma once
#include "BlastHornetState.h"
class BlastHornetPrepare :
	public BlastHornetState
{
public:
	BlastHornetPrepare(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetPrepare();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

