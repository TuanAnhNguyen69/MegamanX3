#include "pch.h"
#include "ShurikenState.h"


ShurikenState::ShurikenState(ShurikenStateHandler * handler, Entity * entity)
{
	this->handler = handler;
	this->entity = entity;
}

ShurikenState::~ShurikenState()
{
}

void ShurikenState::Load()
{
}

void ShurikenState::Update()
{
}

void ShurikenState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
