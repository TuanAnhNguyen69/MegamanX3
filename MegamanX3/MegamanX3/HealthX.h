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

private:
	AnimatedSprite * sprite;
	Player *player;
};

