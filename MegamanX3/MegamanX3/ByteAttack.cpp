#include "pch.h"
#include "ByteAttack.h"


ByteAttack::ByteAttack(ByteStateHandler *handler, Entity *entity) : ByteState(handler, entity)
{
	sprite = new AnimatedSprite(10, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte",
		8, 11, 4, 100, 100);
}


ByteAttack::~ByteAttack()
{
	if (handler->GetCurrentStateName() != ByteStateHandler::StateName::Attack)
	{
		if (sprite)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ByteAttack::Load()
{
	entity->SetSprite(sprite);
	if (handler->IsFaceLeft())
	{
		entity->SetReverse(false);
		entity->SetVelocityX(-Define::BYTE_SPEED);
	}
	else
	{
		entity->SetReverse(true);
		entity->SetVelocityX(Define::BYTE_SPEED);
	}
}

void ByteAttack::Update()
{
	if (handler->IsFaceLeft())
	{
		entity->SetReverse(false);
		entity->AddVelocityX(-Define::BYTE_ACCELERATION);
	}
	else
	{
		entity->SetReverse(true);
		entity->AddVelocityX(Define::BYTE_ACCELERATION);
	}
}

void ByteAttack::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
