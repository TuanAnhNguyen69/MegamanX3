﻿#include "pch.h"
#include "NotorBangerChangeBarrel.h"
#include "NotorBanger.h"



NotorBangerChangeBarrel::NotorBangerChangeBarrel(NotorBangerStateHandler * handler, Entity * entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		5, 7, 5, 50, 50);
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
	sprite->ResetFrame();
	hadStraight = -hadStraight;
}

void NotorBangerChangeBarrel::Update()
{
	if (!handler->GetLeftTarget())
	{
		entity->SetReverse(true);
	}
	else
	{
		entity->SetReverse(false);
	}
	if (handler->GetPreAction() == NotorBangerStateHandler::StateName::Jump)
	{
		if (handler->GetAboveTarget())
		{
			//Sau khi bắn nòng súng sẽ ở tên cao
			hadStraight = true;
			sprite->SetFrameRange(5, 9);	
		}
		else
		{
			//Sau khi bắn nòng súng sẽ nghiêng
			hadStraight = false;
			sprite->SetFrameRange(5, 7);
		}
		if (sprite->IsFinished())
		{
			sprite->ResetFrame();
			handler->ChangeState(NotorBangerStateHandler::StateName::Shoot);
		}
	}
	if (handler->GetPreAction() == NotorBangerStateHandler::StateName::Shoot)
	{
		if (hadStraight)
		{
			sprite->SetFrameRange(10, 14);
			
		}
		else
		{
			sprite->SetFrameRange(12, 14);
		}
		if (sprite->IsFinished())
		{
			//hadStraight = false;
			sprite->ResetFrame();
			handler->ChangeState(NotorBangerStateHandler::StateName::Jump);
		}
	}
	
}

void NotorBangerChangeBarrel::OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
