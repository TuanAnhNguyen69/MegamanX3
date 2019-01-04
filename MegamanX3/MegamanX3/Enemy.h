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

	/*virtual void SubHP(int damage) = 0;
	virtual int GetHP() = 0;*/

protected:
	Player * player;
	int HP;
};

