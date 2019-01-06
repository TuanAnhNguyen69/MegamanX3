#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
class PlayerBullet :
	public Entity
{
public:
	enum BulletState {
		Normal,
		Super,
		Extreme
	};
	PlayerBullet();
	void Initialize(int damage);
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	~PlayerBullet();
private:
	AnimatedSprite *sprite;
	int damage;
};

