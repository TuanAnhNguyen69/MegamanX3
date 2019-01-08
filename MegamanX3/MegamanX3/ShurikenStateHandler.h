#pragma once

namespace Define
{
	const float SHURIKEN_SPEED_ATTACK = 30.0f;			//Vận tốc tấn công
	const float SHURIKEN_ACCELERATION_ATTACK = 15.0f;	//Gia tốc

	const float SHURIKEN_SPEED_JUMP_X = 60.0f;			//Vận tốc nhảy
	const float SHURIKEN_SPEED_JUMP_Y = 60.0f;

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

	virtual void Seen() = 0;
	virtual bool GetSeen() = 0;

	virtual void SetRemove() = 0;
};

#pragma once
