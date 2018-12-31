#pragma once
#include "Entity.h"
#include "Engine.h"

namespace Define
{
	const float BOX_SPEED = 40.0f;		//Vận tốc rơi
}

class Box : public Entity
{
public:
	Box();
	~Box();

	void Update();

	void Initialize(bool isFall);

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	void SetFall(bool isFall);

private:
	AnimatedSprite * sprite;
	bool isFall;
};

