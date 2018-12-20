#pragma once
#include "ShurikenState.h"
class ShurikenAttack2 :
	public ShurikenState
{
public:
	ShurikenAttack2(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenAttack2();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	bool leaveStartPoint;
	D3DXVECTOR3 vAttack;
};

