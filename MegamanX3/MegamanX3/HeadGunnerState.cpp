#include "pch.h"
#include "HeadGunnerState.h"
#include "HeadGunner.h"


HeadGunnerState::HeadGunnerState(HeadGunnerStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = (HeadGunner*)entity;
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



