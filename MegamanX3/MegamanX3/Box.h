#pragma once
#include "Entity.h"
#include "Engine.h"
#include "PlayerBullet.h"

namespace Define
{
	const float BOX_SPEED = 40.0f;		//Vận tốc rơi
}

class Box : public Entity
{
public:
	Box(EntityId id);
	~Box();

	void Update();

	void Initialize(bool isFall);

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	void SetFall(bool isFall);
	bool IsFall();

	bool IsCollisionPlatform();

	int GetHP();
	void SubHP(int damage);

private:
	AnimatedSprite * sprite;
	bool isFall;
	bool isCollPlatform;
	int HP;
	EntityId id;
	bool hadBurst;
};

