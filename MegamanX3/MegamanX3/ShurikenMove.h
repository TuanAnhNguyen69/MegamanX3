#pragma once
#include "ShurikenState.h"
class ShurikenMove :
	public ShurikenState
{
public:
	ShurikenMove(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenMove();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	D3DXVECTOR3 vMove;
	bool leaveStartPoint;
};

