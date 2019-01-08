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
	timeStartState = clock();
	timeCreated = clock();
}

void ByteStanding::Update()
{
	if (!handler->GetSeen())
	{
		timeSeen = clock();
		float dt = (timeSeen - timeCreated) / 1000;
		if (dt > 7)
		{
			handler->Seen();
		}
		return;
	}

	if (handler->IsFaceLeft())
	{
		entity->SetReverse(false);
	}
	else
	{
		entity->SetReverse(true);
	}
	timeCount = clock();
	int dt = (timeCount - timeStartState) / 600;
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
