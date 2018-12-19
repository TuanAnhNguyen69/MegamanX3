#include "pch.h"
#include "ByteState.h"

#include "Byte.h"


ByteState::ByteState(ByteStateHandler *handler, Entity *entity)
{
	this->entity = entity;
	this->handler = handler;
}


ByteState::~ByteState()
{
}

void ByteState::Load()
{
}

void ByteState::Update()
{
}

void ByteState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
