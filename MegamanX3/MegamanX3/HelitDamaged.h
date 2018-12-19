#pragma once
#include "HelitState.h"

class HelitDamaged : public HelitState
{
public:
	HelitDamaged(HelitStateHandler *handler, Entity *entity);
	~HelitDamaged();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

