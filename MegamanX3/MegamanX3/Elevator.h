#pragma once
#include "Entity.h"
#include "Engine.h"

namespace Define
{
	const float ELEVATOR_SPEED = 20.0f;		//Vận tốc
}

class Elevator : Entity
{
public:
	Elevator();
	~Elevator();

	void Update();

	void Initialize(float stopPointX, float stopPointY);

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	AnimatedSprite * sprite;
	D3DXVECTOR3 stopPoint;
	bool isAction;
};

