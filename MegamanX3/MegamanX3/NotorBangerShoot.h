#pragma once
#include "NotorBangerState.h"

class NotorBangerShoot : public NotorBangerState
{
public:
	NotorBangerShoot(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerShoot();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
private:
	int armor;
};