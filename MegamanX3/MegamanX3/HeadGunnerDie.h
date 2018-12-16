#pragma once
#include "HeadGunnerState.h"

class HeadGunnerDie : public HeadGunnerState
{
public:
	HeadGunnerDie(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerDie();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

