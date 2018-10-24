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

private:
	Entity *entity;
};

#endif