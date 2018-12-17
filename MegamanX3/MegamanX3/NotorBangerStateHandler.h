#pragma once

namespace Define
{
	const float NOTORBANGER_MAX_JUMP_VELOCITY = 300.0f; //van toc nhay lon nhat
	const float NOTORBANGER_MIN_JUMP_VELOCITY = -300.0f; //van toc nhay thap nhat
	const float NOTORBANGER_MAX_RUNNING_SPEED = 350.0f; //toc do chay nhanh nhat
	const float NOTORBANGER_BOTTOM_RANGE_FALLING = 6.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi se bi roi xuong
}

class NotorBangerStateHandler
{
protected:
public:
	enum StateName {
		Jump,
		Damaged,
		Shoot,
		Die,
		Standing,
		Falling,
		ChangeBarrel,
	};

	enum MoveDirection
	{
		MoveToLeft,
		MoveToRight,
		None
	};
	
	enum BarrelState
	{
		Straight,
		Inclined,
		Horizontal
	};

	//virtual bool GetAction() = 0;
	//virtual void SetAction(bool action) = 0;
	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;
	virtual void SetPreAction(StateName action) = 0;
	virtual StateName GetPreAction() = 0;
};