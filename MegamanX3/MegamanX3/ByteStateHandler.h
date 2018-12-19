#pragma once

namespace Define
{
	const float BYTE_SPEED = 400.0f;		//Vận tốc húc
	const float BYTE_ACCELERATION = 10.0f;	//Gia tốc húc
}

class ByteStateHandler
{
protected:
	bool isFaceLeft;
public:
	enum StateName {
		Attack,
		Throw,
		Die,
		Standing,
	};

	enum MoveDirection
	{
		MoveToLeft,
		MoveToRight,
		None
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

	virtual bool IsFaceLeft() = 0;
	virtual void SetFace(bool isLeft) = 0;

}; 

#pragma once
