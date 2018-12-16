#pragma once
#include "HeadGunnerState.h"
#include <ctime>

class HeadGunnerStanding : public HeadGunnerState
{
public:
	HeadGunnerStanding(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerStanding();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
private:
	time_t timeChangeState;
};

