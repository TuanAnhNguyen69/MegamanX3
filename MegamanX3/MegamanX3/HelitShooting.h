#pragma once
#include "HelitState.h"
#include "time.h"

class HelitShooting : public HelitState
{
public:
	HelitShooting(HelitStateHandler *handler, Entity *entity);
	~HelitShooting();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	clock_t startState;
	bool hadShoot;
	int ammo;
};

