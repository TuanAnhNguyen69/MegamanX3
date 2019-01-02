#pragma once
#ifndef _BLAST_HORNET_STATE_HANDLER_H
#define _BLAST_HORNET_STATE_HANDLER_H

namespace Define
{
	const float BLASTHORNET_PRICK_SPEED = 50.0f;
	const float BLASTHORNET_RETURN_SPEED = 20.0f;
	const float BLASTHORNET_FLY_SPEED = 20.0f;
	const int BLASTHORNET_HP = 40;
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

	virtual Player* GetPlayer() = 0;

	virtual int GetHP() = 0;

};

#endif