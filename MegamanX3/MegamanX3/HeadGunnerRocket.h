#pragma once
#include "Entity.h"
#include "Engine.h"

class HeadGunnerRocket : public Entity
{
private:
	AnimatedSprite * sprite;
	bool isLeft;
public:
	HeadGunnerRocket();
	~HeadGunnerRocket();

	void Update();

	void Initialize(bool isLeft);

	void OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data);
};

