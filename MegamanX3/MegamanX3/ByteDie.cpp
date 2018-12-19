#include "pch.h"
#include "ByteDie.h"


ByteDie::ByteDie(ByteStateHandler *handler, Entity *entity) : ByteState(handler, entity)
{
}


ByteDie::~ByteDie()
{
	if (handler->GetCurrentStateName() != ByteStateHandler::StateName::Die)
	{
		if (sprite)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ByteDie::Load()
{
}

void ByteDie::Update()
{
}

void ByteDie::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
