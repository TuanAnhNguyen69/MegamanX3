#pragma once
#include "Enemy.h"
#include "Engine.h"

class HelitRocket : public Enemy
{
private:
	AnimatedSprite * sprite;
	bool isLeft;
	bool hitted;
public:
	HelitRocket(Player *player);
	~HelitRocket();

	void Update();

	void Initialize(bool isLeft);

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	bool IsHitted();
};

