#ifndef _PLAYER_STANDING_STATE_H
#define _PLAYER_STANDING_STATE_H

#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(PlayerStateHandler *handler, Entity *entity);
	~PlayerStandingState();

	void Load();
	void Update();
	void UpdateInput();
private:
	AnimatedSprite *standSprite;
	AnimatedSprite *shootSprite;
	bool shooting;
};

#endif