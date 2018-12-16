#pragma once
#ifndef _BLAST_HORNET_STATE_HANDLER_H
#define _BLAST_HORNET_STATE_HANDLER_H

namespace Define
{
	
}

class BlastHornetStateHandler
{
public:
	enum StateName {
		
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

#endif