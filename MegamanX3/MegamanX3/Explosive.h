#pragma once
#include "Entity.h"
#include "Engine.h"
class Explosive : public Entity
{
public:
	Explosive();
	~Explosive();

	void Update();
private:
	AnimatedSprite * sprite;
};

