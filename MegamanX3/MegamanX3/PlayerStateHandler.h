#ifndef _PLAYER_STATE_HANDLER_H
#define _PLAYER_STATE_HANDLER_H

namespace Define
{
	const float PLAYER_MAX_JUMP_VELOCITY = 480.0f; //van toc nhay lon nhat
	const float PLAYER_MIN_JUMP_VELOCITY = -480.0f; //van toc nhay thap nhat
	const float PLAYER_MAX_RUNNING_SPEED = 350.0f; //toc do chay nhanh nhat cua player
	const float PLAYER_BOTTOM_RANGE_FALLING = 6.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
	const float MAX_SLIDE_DISTANCE = 350.0f;

}

class PlayerStateHandler
{
public:
	enum StateName {
		Standing,
		Running,
		Jumping,
		Falling,
		Sliding,
		Damaged,
		Climbing,
		Dying,
		Reviving
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