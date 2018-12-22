#pragma once
#include "BlastHornetState.h"
class BlastHornetReturn : public BlastHornetState
{
public:
	BlastHornetReturn(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetReturn();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	//Vị trí hiện tại khi bắt đầu state Return
	D3DXVECTOR3 curPos;
};

