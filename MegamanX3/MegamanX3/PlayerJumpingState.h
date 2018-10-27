#ifndef _PLAYER_JUMPING_STATE_H
#define _PLAYER_JUMPING_STATE_H

#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	PlayerJumpingState(PlayerStateHandler *handler, Entity *entity);
	~PlayerJumpingState();

	void Load();
	void Update();
	void UpdateInput();

protected:
	float acceleratorX;
	float acceleratorY;
	bool noPressed;
};

#endif