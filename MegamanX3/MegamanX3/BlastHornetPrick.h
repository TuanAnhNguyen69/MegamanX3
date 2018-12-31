#pragma once
#include "BlastHornetState.h"
class BlastHornetPrick : public BlastHornetState
{
public:
	BlastHornetPrick(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetPrick();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	D3DXVECTOR3 targetPos;
};

