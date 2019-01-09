#pragma once
#include "PlayerState.h"
class PlayerReviveState :
	public PlayerState
{
public:
	PlayerReviveState(PlayerStateHandler *handler, Player *entity);
	~PlayerReviveState();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void Load();
	void Update();
	void UpdateInput();
private:
	AnimatedSprite *landSprite, *fallSprite;
};

