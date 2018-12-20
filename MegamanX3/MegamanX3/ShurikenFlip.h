#pragma once
#include "ShurikenState.h"
class ShurikenFlip :
	public ShurikenState
{
public:
	ShurikenFlip(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenFlip();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	clock_t startState;
};

