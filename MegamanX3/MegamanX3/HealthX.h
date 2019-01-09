#pragma once
#include "Enemy.h"

class Entity;

class HealthBar : public Entity
{
public:
	HealthBar(EntityId id);
	~HealthBar();

	void Update(int value, D3DXVECTOR3 pos);
	void Initialize();

private:
	AnimatedSprite * sprite;
	EntityId id;
};

