#pragma once
#include "HelitState.h"

class HelitShooting : public HelitState
{
public:
	HelitShooting(HelitStateHandler *handler, Entity *entity);
	~HelitShooting();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

