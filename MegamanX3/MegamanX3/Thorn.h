#pragma once
#include "Entity.h"
#include "Engine.h"

class Thorn : public Entity
{
public:
	Thorn();
	~Thorn();
	void Update();

	void Initialize(bool isLeft);

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	AnimatedSprite * sprite;
};

