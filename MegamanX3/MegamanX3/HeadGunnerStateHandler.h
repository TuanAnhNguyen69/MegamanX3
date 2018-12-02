#pragma once
class HeadGunnerStateHandler
{
public:	

	enum StateName {
		Damaged,
		Fire,
		Die,
		Standing
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

