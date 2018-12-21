#pragma once

#include "Engine.h"
#include "PlayerStateHandler.h"
#include "PlayerState.h"
#include "Camera.h"

class Platform : public Entity
{
public:
	Platform();
	void Update();
	void Initialize();
	~Platform();
};

