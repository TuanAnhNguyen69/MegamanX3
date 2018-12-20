#pragma once
#include "ShurikenState.h"
class ShurikenJump :
	public ShurikenState
{
public:
	ShurikenJump(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenJump();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	bool isJumping;
	bool leaveStartPoint;
	D3DXVECTOR3 vJump;
	D3DXVECTOR3 aJump;
};

