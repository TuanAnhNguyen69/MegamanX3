#pragma once
#include "Entity.h"
#include "Engine.h"

class HelitRocket : public Entity
{
private:
	AnimatedSprite * sprite;
	bool isLeft;
public:
	HelitRocket();
	~HelitRocket();

	void Update();

	void Initialize(bool isLeft);

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

