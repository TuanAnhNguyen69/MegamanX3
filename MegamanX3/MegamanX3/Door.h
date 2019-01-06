#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"

class Door : public Entity
{
public:
	enum DoorState { OPENED, OPENNING, CLOSED, CLOSING };
	Door();
	~Door();
	void Update();
	void Initialize();
	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	DoorState GetState();
	void SetState(DoorState state);

private:
	AnimatedSprite * closedSprite;
	AnimatedSprite * openningSprite;
	AnimatedSprite * closingSprite;
	AnimatedSprite * openedSprite;
	DoorState state;
};

