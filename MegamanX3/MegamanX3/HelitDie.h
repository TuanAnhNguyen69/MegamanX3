#pragma once
#include "HelitState.h"

class HelitDie : public HelitState
{
public:
	HelitDie(HelitStateHandler *handler, Entity *entity);
	~HelitDie();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

