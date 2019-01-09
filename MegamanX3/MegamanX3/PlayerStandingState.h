#ifndef _PLAYER_STANDING_STATE_H
#define _PLAYER_STANDING_STATE_H

#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(PlayerStateHandler *handler, Player *entity);
	~PlayerStandingState();

	void Load();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void Update();
	void UpdateInput();
private:
	AnimatedSprite *standSprite;
	AnimatedSprite *shootSprite;
	bool shooting;
	void OnConveyorCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

#endif