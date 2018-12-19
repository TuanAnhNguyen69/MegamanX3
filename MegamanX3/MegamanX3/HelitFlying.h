#pragma once
#include "HelitState.h"

class HelitFlying : public HelitState
{
public:
	HelitFlying(HelitStateHandler *handler, Entity *entity);
	~HelitFlying();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

