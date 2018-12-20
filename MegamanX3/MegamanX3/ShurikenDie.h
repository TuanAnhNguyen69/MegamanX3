#pragma once
#include "ShurikenState.h"
class ShurikenDie :
	public ShurikenState
{
public:
	ShurikenDie(ShurikenStateHandler *handler, Entity *entity);
	~ShurikenDie();
};

