#pragma once
#include "Entity.h"
#include "Player.h"
#include "PlayerBullet.h"
class Enemy : public Entity
{
public:
	Enemy(EntityId entityId, Player * player);
	~Enemy();
	void Update();
	bool IsActive();
	void SetActive(bool active);
	
	void SubHP(int damage);
	int GetHP();

	Player * player;

protected:
	void SetActiveRange(int activeRange);
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	bool active;
	int activeRange;
	int GetPlayerDistance();
	int HP;
};

