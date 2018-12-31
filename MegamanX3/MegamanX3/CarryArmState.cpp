#include "pch.h"
#include "CarryArmState.h"
#include "CarryArm.h"


CarryArmState::CarryArmState(CarryArmStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = (CarryArm*)entity;
}

CarryArmState::~CarryArmState()
{

}

void CarryArmState::Load()
{
}

void CarryArmState::Update()
{
}

void CarryArmState::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}



