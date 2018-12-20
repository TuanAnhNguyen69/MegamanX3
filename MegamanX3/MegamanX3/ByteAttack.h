#pragma once
#include "ByteState.h"
class ByteAttack :
	public ByteState
{
public:
	ByteAttack(ByteStateHandler *handler, Entity *entity);
	~ByteAttack();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	bool isMove;

};

