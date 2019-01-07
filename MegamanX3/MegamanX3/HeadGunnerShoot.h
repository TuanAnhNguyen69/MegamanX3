#pragma once
#include "HeadGunnerState.h"
#include "HeadGunnerRocket.h"
#include "Canon.h"
#include "time.h"

class HeadGunnerShoot : public HeadGunnerState
{
public:
	HeadGunnerShoot(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerShoot();

	void Load();
	void Update();
	void OnCollision(Entity *impactor,  Entity::CollisionSide side, Entity::CollisionReturn data);
private:

	bool hadShootRocket;
	bool hadShootCanon;
	int ammo;
};

