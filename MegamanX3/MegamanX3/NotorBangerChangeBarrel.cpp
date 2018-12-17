#include "pch.h"
#include "NotorBangerChangeBarrel.h"
#include "NotorBanger.h"



NotorBangerChangeBarrel::NotorBangerChangeBarrel(NotorBangerStateHandler * handler, Entity * entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(5, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		5, 9, 5, 50, 50);
}

NotorBangerChangeBarrel::~NotorBangerChangeBarrel()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::ChangeBarrel) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerChangeBarrel::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void NotorBangerChangeBarrel::Update()
{
	if (handler->GetPreAction() == NotorBangerStateHandler::StateName::Jump)
	{
		if (hadStraight)
		{
			sprite->SetFrameRange(0, 2);
			if (sprite->IsFinished())
			{
				hadStraight = false;
				handler->ChangeState(NotorBangerStateHandler::StateName::Shoot);
			}
		}
		else
		{
			sprite->SetFrameRange(0, 4);
			if (sprite->IsFinished())
			{
				hadStraight = true;
				handler->ChangeState(NotorBangerStateHandler::StateName::Shoot);
			}
		}
	}
	if (handler->GetPreAction() == NotorBangerStateHandler::StateName::Shoot)
	{
		if (hadStraight)
		{
			sprite->SetFrameRange(0, 2);
			if (sprite->IsFinished())
			{
				hadStraight = false;
				handler->ChangeState(NotorBangerStateHandler::StateName::Jump);
			}
		}
		else
		{
			sprite->SetFrameRange(0, 4);
			if (sprite->IsFinished())
			{
				hadStraight = true;
				handler->ChangeState(NotorBangerStateHandler::StateName::Jump);
			}
		}
	}
	
}

void NotorBangerChangeBarrel::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
