#pragma once
#include "PlayerState.h"
class PlayerDieState :
	public PlayerState
{
public:
	PlayerDieState(PlayerStateHandler *handler, Player *entity);
	~PlayerDieState();

	void Load();
	void Update();
	void UpdateInput();
private:
	int spriteLoopTimes;
};

