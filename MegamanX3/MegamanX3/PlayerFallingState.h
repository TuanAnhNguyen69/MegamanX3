#ifndef _PLAYER_FALLING_STATE_H
#define _PLAYER_FALLING_STATE_H

#include "PlayerState.h"

class PlayerFallingState : public PlayerState
{
public:
	enum BlockType
	{
		BlockLeft,
		BlockRight,
		None
	};

	PlayerFallingState(PlayerStateHandler *handler, Player *entity);
	~PlayerFallingState();

	void Load();
	void Update();
	void UpdateInput();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

protected:
	BlockType blockType;
	float acceleratorX;
	float acceleratorY;
	bool isLeftOrRightKeyPressed;
};

#endif