#pragma once
#include "Engine.h"
#include "Entity.h"
class Life : public Entity
{
private:
	AnimatedSprite * sprite;
public:
	Life();
	~Life();

	void Initialize();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

