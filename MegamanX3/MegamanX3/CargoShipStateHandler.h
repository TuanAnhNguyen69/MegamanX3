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

	CargoSole *sole;

};