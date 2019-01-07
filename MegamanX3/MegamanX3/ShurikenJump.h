#pragma once
#include "ShurikenState.h"
class ShurikenJump :
	public ShurikenState
{
public:
	enum Route
	{
		AtStartPoint,
		AtWallPoint,
		Unknow,
	};
	ShurikenJump(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenJump();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	void JumpTo(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float far, float high);

private:
	bool hadLeaveStartPoint;

	D3DXVECTOR3 startPoint, wallPoint;

	Route route;
	bool isUp;
};

