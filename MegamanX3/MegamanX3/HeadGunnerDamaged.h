#pragma once
#include "HeadGunnerState.h"

class HeadGunnerDamaged : public HeadGunnerState
{
public:
	HeadGunnerDamaged(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerDamaged();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

