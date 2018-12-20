#pragma once
#include "ShurikenState.h"
class ShurikenAttack1 : public ShurikenState
{
public:
	ShurikenAttack1(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenAttack1();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	D3DXVECTOR3 vAttack;
	bool leaveStartPoint;
	bool passJumpPoint;

};

