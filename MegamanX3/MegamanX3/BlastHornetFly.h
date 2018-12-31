#pragma once
#include "BlastHornetState.h"
class BlastHornetFly :
	public BlastHornetState
{
public:
	BlastHornetFly(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetFly();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

