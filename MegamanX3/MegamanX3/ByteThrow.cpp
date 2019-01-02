#include "pch.h"
#include "ByteThrow.h"


ByteThrow::ByteThrow(ByteStateHandler *handler, Entity *entity) : ByteState(handler, entity)
{
	sprite = new AnimatedSprite(8, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte",
		8, 11, 4, 100, 100);
}


ByteThrow::~ByteThrow()
{
	if (handler->GetCurrentStateName() != ByteStateHandler::StateName::Throw)
	{
		if (sprite)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ByteThrow::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadThrow = false;
	handler->SetPreAction(ByteStateHandler::StateName::Throw);
}

void ByteThrow::Update()
{
	if (handler->IsFaceLeft())
	{
		entity->SetReverse(false);
	}
	else
	{
		entity->SetReverse(true);
	}

	//if (sprite->GetCurrentFrame() == 2 && !hadThrow)
	if(!hadThrow)
	{
		ByteBomb *bomb = new ByteBomb();
		if (handler->IsFaceLeft())
		{		
			bomb->SetPosition(entity->GetPosition().x + -60, entity->GetPosition().y + 10);
			bomb->Initailize(ByteBomb::MoveDirection::Left);
		}
		else
		{
			bomb->SetPosition(entity->GetPosition().x + 20, entity->GetPosition().y + 10);
			bomb->Initailize(ByteBomb::MoveDirection::Right);
		}
		bomb->SetScale(2, 2);
		bomb->SetBound(15*2, 15*2);
		EntityManager::GetInstance()->AddEntity(bomb);
		hadThrow = true;
	}

	if (sprite->IsFinished())
	{
		handler->ChangeState(ByteStateHandler::StateName::Standing);
	}
}

void ByteThrow::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
