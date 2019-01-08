#pragma once
#include "Entity.h"
#include "Engine.h"

namespace Define
{
	const float ELEVATOR_SPEED = -1.0f;	
	const float MAX_DISTANCE = 1020.0f;	//Vận tốc
}

class Elevator : public Entity
{
public:
	Elevator();
	~Elevator();

	void Update();
	int GetSpeed();
	bool IsActive();
	void Initialize();

	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

private:
	AnimatedSprite * sprite;
	D3DXVECTOR3 stopPoint;
	bool active;
	int speed;
	float traveledDistance;
};

