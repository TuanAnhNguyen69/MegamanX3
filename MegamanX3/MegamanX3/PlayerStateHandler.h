#ifndef _PLAYER_STATE_HANDLER_H
#define _PLAYER_STATE_HANDLER_H

class PlayerStateHandler
{
public:
	enum StateName {
		Standing,
		Running,
		Jumping,
		Falling
	};

	enum MoveDirection
	{
		MoveToLeft,
		MoveToRight,
		None
	};

	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;
};

#endif