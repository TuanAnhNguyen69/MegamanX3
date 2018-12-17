#pragma once
#include "HeadGunnerState.h"
#include "HeadGunnerRocket.h"

class HeadGunnerShoot : public HeadGunnerState
{
public:
	HeadGunnerShoot(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerShoot();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
private:
	bool hadShoot;
};

