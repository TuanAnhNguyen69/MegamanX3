#pragma once
#ifndef _BLAST_HORNET_STATE_HANDLER_H
#define _BLAST_HORNET_STATE_HANDLER_H

namespace Define
{
	const float BLASTHORNET_PRICK_SPEED_X = 0.0f;
	const float BLASTHORNET_PRICK_SPEED_Y = 0.0f;
	const float BLASTHORNET_RETURN_SPEED_X = 10.0f;
	const float BLASTHORNET_RETURN_SPEED_Y = 10.0f;
	const float BLASTHORNET_FLY_SPEED_X = 0.0f;
	const float BLASTHORNET_FLY_SPEED_Y = 0.0f;

}

class BlastHornetStateHandler
{
public:
	enum StateName {
		Fly,
		Prepare,
		Return,
		Prick,
		Drop,
		Die,
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

	virtual StateName GetPreAction() = 0;
	virtual void SetPreAction(StateName action) = 0;

	virtual D3DXVECTOR3 GetPlayerPos() = 0;

	virtual D3DXVECTOR3 GetPointA() = 0;
	virtual D3DXVECTOR3 GetPointB() = 0;

};

#endif