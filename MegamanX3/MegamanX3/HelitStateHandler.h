#pragma once
class HelitStateHandler
{
protected:
public:
	enum StateName {
		Damaged,
		Shooting,
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
	virtual bool GetHadShootState() = 0;
	virtual void SetHadShootState(bool hadShootState) = 0;	

	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;
};

