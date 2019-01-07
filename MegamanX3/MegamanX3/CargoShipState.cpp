#include "pch.h"
#include "CargoShipState.h"



CargoShipState::CargoShipState(CargoShipStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = entity;
}


CargoShipState::~CargoShipState()
{
}

void CargoShipState::Load()
{
}

void CargoShipState::Update()
{
}

void CargoShipState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
