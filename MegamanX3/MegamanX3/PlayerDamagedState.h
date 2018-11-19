#pragma once
#include "PlayerState.h"
class PlayerDamagedState :
	public PlayerState
{
public:
	PlayerDamagedState(PlayerStateHandler *handler, Entity *entity);
	~PlayerDamagedState();
	void Load();
	void Update();
	void UpdateInput();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};
