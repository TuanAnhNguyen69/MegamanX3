#pragma once
#include "BlastHornetState.h"
#include <list>
#include <time.h>

class BlastHornetFly : public BlastHornetState
{
public:
	enum Route
	{
		AtIntersection,
		AtPoint1,
		AtPoint2,
		AtPoint3,
		AtPoint4,
		Unknow,
	};

	BlastHornetFly(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetFly();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	D3DXVECTOR3 startPoint;

	D3DXVECTOR3 intersectionPoint;

	D3DXVECTOR3 point1;
	D3DXVECTOR3 point2;
	D3DXVECTOR3 point3;
	D3DXVECTOR3 point4;

	Route route;
	bool hadDrop;
};

