#pragma once
#include "Entity.h"
#include "Player.h"
class Enemy :
	public Entity
{
public:
	Enemy(EntityId entityId, Player * player);
	~Enemy();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
private:
	Player * player;
};

