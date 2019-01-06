#pragma once
#include "Entity.h"

class DownPlatform :public Entity
{
public:
	DownPlatform();
	void Update();
	void Initialize();
	int GetCollidePosition(Entity *entity);
	~DownPlatform();
};

