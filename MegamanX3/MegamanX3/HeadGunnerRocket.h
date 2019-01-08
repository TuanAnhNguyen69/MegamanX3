#pragma once
#include "Engine.h"
#include "Enemy.h"

class HeadGunnerRocket : public Enemy
{
private:
	AnimatedSprite * sprite;
	bool isLeft;
	bool hitted;
public:
	HeadGunnerRocket(Player *player);
	~HeadGunnerRocket();

	void Update();

	void Initialize(bool isLeft);

	void OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data);

	bool IsHitted();
};

