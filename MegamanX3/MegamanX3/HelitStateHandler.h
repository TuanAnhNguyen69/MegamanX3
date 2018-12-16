#pragma once
class HelitStateHandler
{
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

	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;
};

