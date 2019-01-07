#ifndef _ENEMY_STATE_H
#define _ENEMY_STATE_H

#include "Engine.h"
#include "Entity.h"
#include "BlastHornetStateHandler.h"
#include "AnimatedSprite.h"
#include "Bee.h"
#include <time.h>

class BlastHornetState
{
public:
	BlastHornetState(BlastHornetStateHandler *handler, Entity *entity);
	~BlastHornetState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	float UCLN(float a, float b);

	//void GoTo(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed);
	//void GoOn(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed);

protected:
	AnimatedSprite *sprite;
	BlastHornetStateHandler *handler;
	Entity *entity;
	bool isGoToPointA;
	clock_t timeStartState;
	clock_t timeCount;
};

#endif