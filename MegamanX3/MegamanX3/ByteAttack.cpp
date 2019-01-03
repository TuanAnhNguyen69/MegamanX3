#include "pch.h"
#include "ByteAttack.h"


ByteAttack::ByteAttack(ByteStateHandler *handler, Entity *entity) : ByteState(handler, entity)
{
	sprite = new AnimatedSprite(10, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte",
		4, 6, 4, 100, 100);
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
	entity->SetVelocity(0, 0);
	isMove = false;
	handler->SetPreAction(ByteStateHandler::StateName::Attack);
	if (sprite->IsFinished())
	{
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
}

void ByteAttack::Update()
{
	if (sprite->IsFinished())
	{
		if (!isMove)
		{
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
			isMove = true;
		}
		if (handler->IsFaceLeft())
		{
			//entity->SetReverse(false);
			entity->AddVelocityX(-Define::BYTE_ACCELERATION);
		}
		else
		{
			//entity->SetReverse(true);
			entity->AddVelocityX(Define::BYTE_ACCELERATION);
		}
	}
}

void ByteAttack::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == ByteBomb_ID)
	{
		switch (side)
		{

		case Entity::Left:
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 60, 0);
			entity->SetVelocityX(0);
			handler->SetFace(false);
			handler->ChangeState(ByteStateHandler::StateName::Standing);
			break;

		case Entity::Right:
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left) - 60, 0);
			entity->SetVelocityX(0);
			handler->SetFace(true);
			handler->ChangeState(ByteStateHandler::StateName::Standing);
			break;
		}
	}
}
