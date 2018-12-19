#pragma once
#include "Entity.h"
#include "Engine.h"

class HeadGunnerRocket : public Entity
{
private:
	AnimatedSprite * sprite;
public:
	HeadGunnerRocket(bool isLeft, bool isTop);
	~HeadGunnerRocket();

	void Update();

	void Initialize();

	void OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data);
};

