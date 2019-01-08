#pragma once
#include "Enemy.h"

class Entity;

class HealthX : public Entity
{
public:
	HealthX(Player *player);
	~HealthX();

	void Update();
	void Initialize();
	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	AnimatedSprite * sprite;
	Player *player;
};

