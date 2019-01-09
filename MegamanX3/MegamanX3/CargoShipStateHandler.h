#pragma once
#include "CargoSole.h"
class CargoShipStateHandler
{
protected:
public:
	enum StateName {
		Up,
		Down,
		Drop,
	};

	virtual StateName GetCurrentStateName() = 0;
	virtual void ChangeState(StateName state) = 0;

	virtual D3DXVECTOR3 GetOriginalSolePos() = 0;
	virtual void SetRemoveSole() = 0;

	CargoSole *sole;

	virtual void SetRemove() = 0;

};