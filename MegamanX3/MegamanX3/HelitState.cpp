#include "pch.h"
#include "HelitState.h"
#include "Helit.h"


HelitState::HelitState(HelitStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = (Helit*)entity;
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

void HelitState::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}



