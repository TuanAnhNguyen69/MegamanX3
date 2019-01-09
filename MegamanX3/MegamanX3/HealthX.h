#pragma once
#include "Enemy.h"

class Entity;

class HealthBar : public Entity
{
public:
	HealthBar();
	~HealthBar();

	void Update(int value, D3DXVECTOR3 pos);
	void Initialize();
	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	AnimatedSprite * sprite;
};

