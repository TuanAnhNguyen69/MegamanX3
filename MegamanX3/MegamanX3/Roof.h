#pragma once
#include "Entity.h"
class Roof :
	public Entity
{
public:
	Roof();
	void Update();
	void Initialize();
	int GetCollidePosition(Entity *entity);
	~Roof();
};

