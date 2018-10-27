#ifndef _PLAYER_H
#define _PLAYER_H

#include "Engine.h"

class Entity;

class Player
{
public:
	Player();
	~Player();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void UpdateInput();

	void SetPosition(int x, int y);
	D3DXVECTOR3 GetPosition();

private:
	Entity *entity;
};

#endif