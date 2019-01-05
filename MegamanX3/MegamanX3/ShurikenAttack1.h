#pragma once
#include "ShurikenState.h"
class ShurikenAttack1 : public ShurikenState
{
public:
	enum Route
	{
		AtStartPoint,
		AtJumpPoint,
		AtWallPoint,
		Unknow,
	};

	ShurikenAttack1(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenAttack1();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	bool hadLeaveStartPoint;
	bool hadPassJumpPoint;

	D3DXVECTOR3 jumpPoint;
	D3DXVECTOR3 wallPoint;
	D3DXVECTOR3 startPoint;

	Route route;
};

