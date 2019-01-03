#pragma once
#include "Entity.h"
#include "Player.h"
class Enemy : public Entity
{
public:
	Enemy(EntityId entityId, Player * player);
	~Enemy();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	void SubHP(int damage);
	int GetHP();

protected:
	Player * player;
	int HP;
};

