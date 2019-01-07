#pragma once
#include "HeadGunnerState.h"
#include "HeadGunnerRocket.h"
class HeadGunnerShootRocket :
	public HeadGunnerState
{
public:
	HeadGunnerShootRocket(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerShootRocket();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	bool isLeft;
	bool hadShoot;
	int ammo;
};

