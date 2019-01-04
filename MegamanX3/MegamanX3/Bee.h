#pragma once
#include "Engine.h"
#include "Enemy.h"
#include <time.h>

namespace Define
{
	const float BEE_SPEED = 15.0;
	const float BEE_FOLLOW_SPEED = 7.0f;
}

class Bee : public Entity
{
public:
	Bee(Player *player);
	Bee(D3DXVECTOR3 desPost);
	~Bee();

	void Initailize();
	void Update();
	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void GoOn(D3DXVECTOR3 desPoint);
	void Follow();

private:
	AnimatedSprite * sprite;
	D3DXVECTOR3 startPos;
	D3DXVECTOR3 desPos;
	bool isFollow;
	Player *player;
	clock_t timeBorn;
	clock_t timeCount;
	bool isStop;
};

