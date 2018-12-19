#include "pch.h"
#include "NotorBangerState.h"
#include "NotorBanger.h"

NotorBangerState::NotorBangerState(NotorBangerStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = (NotorBanger*)entity;
}
#
NotorBangerState::~NotorBangerState()
{
}

void NotorBangerState::Load()
{
}

void NotorBangerState::Update()
{
}

void NotorBangerState::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}




