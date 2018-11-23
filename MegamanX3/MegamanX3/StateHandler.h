#pragma once
class StateHandler
{
public:
	StateHandler();
	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;
	virtual MoveDirection GetMoveDirection() = 0;
	~StateHandler();
};

