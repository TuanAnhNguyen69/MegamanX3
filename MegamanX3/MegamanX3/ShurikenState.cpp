#include "pch.h"
#include "ShurikenState.h"


ShurikenState::ShurikenState(ShurikenStateHandler * handler, Entity * entity)
{
	this->handler = handler;
	this->entity = entity;
	startPoint = entity->GetPosition();
	jumpPoint = D3DXVECTOR3(startPoint.x - 400, startPoint.y, 0);
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
