#pragma once

#include "Engine.h"
#include "PlayerStateHandler.h"
#include "PlayerState.h"
#include "Camera.h"

class Platform
{
public:
	Platform();
	~Platform();
	void Initialize(LPDIRECT3DDEVICE9 device, Camera *camera);
	void Update();
	void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();
};

