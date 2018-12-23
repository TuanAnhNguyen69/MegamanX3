#pragma once
#include "PlayerState.h"

class PlayerSlidingState :
	public PlayerState
{
public:
	PlayerSlidingState(PlayerStateHandler *handler, Player *entity);
	~PlayerSlidingState();
	void Load();
	void Update();
	void UpdateInput();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	float acceleratorX;
	float slidedDistance;
	AnimatedSprite *slideSprite;
	AnimatedSprite *fireSprite;
	void OnPlatformCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnRoofCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnUpPlatformCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
	void OnDownPlatformCollide(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};

