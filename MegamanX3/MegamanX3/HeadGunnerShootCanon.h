#pragma once
#include "HeadGunnerState.h"
#include "Canon.h"
class HeadGunnerShootCanon :
	public HeadGunnerState
{
public:
	HeadGunnerShootCanon(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerShootCanon();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	bool isLeft;
	bool hadShoot;
};

