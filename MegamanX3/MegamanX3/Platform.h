#pragma once

#include "Engine.h"
#include "PlayerStateHandler.h"
#include "PlayerState.h"
#include "Camera.h"

class Platform : public Entity
{
public:
	Platform();
	~Platform();
	void Initialize();
};

