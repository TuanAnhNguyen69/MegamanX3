#pragma once
#include "Entity.h"
#include "Engine.h"

class CargoSole : public Entity
{
public:
	CargoSole();
	~CargoSole();

	void Initialize();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	//RECT GetBound();

	bool HadAlight();
	void SetRemove();

private:
	AnimatedSprite * sprite;
	bool alight;
	bool remove;
};

