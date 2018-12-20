#pragma once
#include "ShurikenState.h"
class ShurikenTurn : public ShurikenState
{
public:
	ShurikenTurn(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenTurn();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	clock_t startState;
};

