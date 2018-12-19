#pragma once
#include "PlayerState.h"

class PlayerSlidingState :
	public PlayerState
{
public:
	PlayerSlidingState(PlayerStateHandler *handler, Entity *entity);
	~PlayerSlidingState();
	void Load();
	void Update();
	void UpdateInput();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	float acceleratorX;
	float slidedDistance;
};

