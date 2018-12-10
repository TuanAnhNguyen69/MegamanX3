#pragma once
class NotorBangerStateHandler
{
protected:
	bool action;
public:
	enum StateName {
		Jump,
		Damaged,
		Fire,
		Die,
		Standing,
		Falling,
	};

	enum MoveDirection
	{
		MoveToLeft,
		MoveToRight,
		None
	};

	virtual bool GetAction() = 0;
	virtual void SetAction(bool action) = 0;
	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;
};