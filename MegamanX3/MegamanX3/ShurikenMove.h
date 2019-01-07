#pragma once
#include "ShurikenState.h"
class ShurikenMove :
	public ShurikenState
{
public:
	enum Route
	{
		AtPoint1,
		AtPoint2,
		AtPoint3,
		AtPoint4,
		Unknow,
	};
	ShurikenMove(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenMove();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	bool hadLeaveStartPoint;

	D3DXVECTOR3 point1, point2, point3, point4;

	Route route;
};

