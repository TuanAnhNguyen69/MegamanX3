#pragma once
class CarryArmStateHandler
{
protected:
public:
	enum StateName {
		Damaged,
		Dropping,
		Die,
		Flying
	};

	enum MoveDirection
	{
		MoveToTop,
		MoveToBottom,
		None
	};
	virtual bool GetLeftTarget() = 0;
	virtual bool GetAboveTarget() = 0;
	virtual bool GetHadDropState() = 0;
	virtual void SetHadDropState(bool hadDropState) = 0;
	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;

};

