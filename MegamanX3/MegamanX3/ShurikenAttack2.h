#pragma once
#include "ShurikenState.h"
class ShurikenAttack2 :
	public ShurikenState
{
public:
	enum Route
	{
		AtStartPoint,
		AtWallPoint,
		Unknow,
	};
	ShurikenAttack2(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenAttack2();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	bool hadLeaveStartPoint;

	D3DXVECTOR3 wallPoint;
	D3DXVECTOR3 startPoint;

	Route route;
};

