#pragma once
#include "Enemy.h"
#include "Entity.h"
const float CANON_MAX_JUMP_VELOCITY = 600.0f; //van toc nhay lon nhat
const float CANON_MIN_JUMP_VELOCITY = -600.0f; //van toc nhay thap nhat
const float CANON_MAX_RUNNING_SPEED = 500.0f; //toc do chay nhanh nhat
class Canon : public Entity
{
public:
	Canon();
	~Canon();

	void Update();

	void Initialize(bool _isHigh);

	void OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

private:
	AnimatedSprite * sprite;
	bool isHigh;
	float x0;
	float y0;
};

