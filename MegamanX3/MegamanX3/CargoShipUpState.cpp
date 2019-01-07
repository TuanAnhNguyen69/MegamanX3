#include "pch.h"
#include "CargoShipUpState.h"


CargoShipUpState::CargoShipUpState(CargoShipStateHandler *handler, Entity *entity) : CargoShipState(handler, entity)
{
}


CargoShipUpState::~CargoShipUpState()
{
}

void CargoShipUpState::Load()
{
}

void CargoShipUpState::Update()
{
}

void CargoShipUpState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
