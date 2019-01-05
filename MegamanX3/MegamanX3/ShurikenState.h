#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "Engine.h"
#include "ShurikenStateHandler.h"
#include <time.h>


class ShurikenState
{
public:
	ShurikenState(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	ShurikenStateHandler *handler;
	Entity *entity;

	/*D3DXVECTOR3 startPoint;
	D3DXVECTOR3 jumpPoint;*/

	clock_t timeStartState, timeCount;
};

