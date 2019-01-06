#pragma once

namespace Define
{
	const float NOTORBANGER_MAX_JUMP_VELOCITY = 600.0f; //van toc nhay lon nhat
	const float NOTORBANGER_MIN_JUMP_VELOCITY = -600.0f; //van toc nhay thap nhat
	const float NOTORBANGER_MAX_RUNNING_SPEED = 500.0f; //toc do chay nhanh nhat
	const float NOTORBANGER_BOTTOM_RANGE_FALLING = 6.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi se bi roi xuong
}

class NotorBangerStateHandler
{
protected:
	bool targetIsLeft;
	bool targetIsAbove;
	bool hadChangeHigh;
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
	virtual bool GetLeftTarget() = 0;
	virtual bool GetAboveTarget() = 0;
	//virtual bool GetAction() = 0;
	//virtual void SetAction(bool action) = 0;
	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;
	virtual void SetPreAction(StateName action) = 0;
	virtual StateName GetPreAction() = 0;

	virtual D3DXVECTOR3 GetPlayerPos() = 0;
	virtual bool HadChangeHigh() = 0;
	virtual void SetHadChangeHigh(bool hadChangeHigh) = 0;
};