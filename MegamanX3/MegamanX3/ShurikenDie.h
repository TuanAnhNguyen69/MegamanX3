#pragma once
#include "ShurikenState.h"
#include "Explosive.h"
class ShurikenDie :
	public ShurikenState
{
public:
	ShurikenDie(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenDie();
	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
};

