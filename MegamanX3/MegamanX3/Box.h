#pragma once
#include "Enemy.h"
#include "Engine.h"
#include "PlayerBullet.h"

class Entity;

namespace Define
{
	const float BOX_SPEED = 40.0f;		//Vận tốc rơi
}

class Box : public Enemy
{
public:
	Box(EntityId id, Player *player);
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
	EntityId id;
	bool hadBurst;
};

