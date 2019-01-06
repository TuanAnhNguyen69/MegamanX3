#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"

class Door : public Entity
{
	enum DoorState{ OPENED, OPENNING, CLOSED, CLOSING};
public:
	Door();
	~Door();
	void Update();
	void Initialize();
	void OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	DoorState GetState();

private:
	AnimatedSprite * closedSprite;
	AnimatedSprite * openningSprite;
	AnimatedSprite * closingSprite;
	AnimatedSprite * openedSprite;
	DoorState state;
};

