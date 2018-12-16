#include "pch.h"
#include "HeadGunnerState.h"


HeadGunnerState::HeadGunnerState(HeadGunnerStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = entity;
}

HeadGunnerState::~HeadGunnerState()
{
	
}

void HeadGunnerState::Load()
{
}

void HeadGunnerState::Update()
{
}

void HeadGunnerState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}



