#include "pch.h"
#include "HelitState.h"


HelitState::HelitState(HelitStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = entity;
}

HelitState::~HelitState()
{

}

void HelitState::Load()
{
}

void HelitState::Update()
{
}

void HelitState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}



