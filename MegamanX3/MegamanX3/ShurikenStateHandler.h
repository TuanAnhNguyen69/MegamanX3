#pragma once

namespace Define
{
	const float SHURIKEN_SPEED_ATTACK = 400.0f;			//Vận tốc tấn công
	const float SHURIKEN_ACCELERATION_ATTACK = 15.0f;	//Gia tốc
	const float SHURIKEN_SPEED_MOVE = 250.0f;			//Vận tốc đi quanh màn hình
	const float SHURIKEN_SPEED_JUMP_X = 200.0f;			//Vận tốc nhảy
	const float SHURIKEN_SPEED_JUMP_Y = 300.0f;
	const float SHURIKEN_ACCELERATION_JUMP_X = 10.0f;	//Gia tốc nhảy
	const float SHURIKEN_ACCELERATION_JUMP_Y = 15.0f;

	const float SHURIKEN_ACCELERATION_FALL_Y = 15.0f;	//Gia tốc rơi
}

class ShurikenStateHandler
{
protected:

public:
	enum StateName {
		Jump,
		Turn,
		Attack1,
		Attack2,
		Die,
		Flip,
		Move,
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
};

#pragma once
