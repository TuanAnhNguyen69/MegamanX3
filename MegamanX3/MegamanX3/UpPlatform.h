#pragma once
#include "Entity.h"

class UpPlatform : public Entity
{
public:
	UpPlatform();
	void Update();
	void Initialize();
	int GetCollidePosition(Entity *entity);
	~UpPlatform();
};

