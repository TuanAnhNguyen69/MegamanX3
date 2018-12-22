#include "pch.h"
#include "ByteStanding.h"


ByteStanding::ByteStanding(ByteStateHandler *handler, Entity *entity) : ByteState(handler, entity)
{
	sprite = new AnimatedSprite(10, 0.5, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte",
		0, 1, 4, 100, 100);

}


ByteStanding::~ByteStanding()
{
	if (handler->GetCurrentStateName() != ByteStateHandler::StateName::Standing)
	{
		if (sprite)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ByteStanding::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	startState = clock();
}

void ByteStanding::Update()
{
	if(handler->IsFaceLeft())
	{
		entity->SetReverse(false);
	}
	else
	{
		entity->SetReverse(true);
	}
	clock_t cout = clock();
	int dt = (cout - startState) / 600;
	if (dt > 3)
	{
		if (handler->GetPreAction() == ByteStateHandler::StateName::Throw)
		{
			handler->ChangeState(ByteStateHandler::StateName::Attack);
		}
		else if (handler->GetPreAction() == ByteStateHandler::StateName::Attack)
		{
			handler->ChangeState(ByteStateHandler::StateName::Throw);
		}
	}
}

void ByteStanding::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
