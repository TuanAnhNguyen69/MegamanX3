#include "pch.h"
#include "NotorBangerShoot.h"
#include "NotorBanger.h"


NotorBangerShoot::NotorBangerShoot(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(5, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		15, 24, 5, 50, 50);
}

NotorBangerShoot::~NotorBangerShoot()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Shoot) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerShoot::Load()
{
	armor = 5;
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;
	handler->SetPreAction(NotorBangerStateHandler::StateName::Shoot);
}

void NotorBangerShoot::Update()
{
	//nếu nòng súng không ở trên cao
	if (!hadStraight)
	{
		sprite->SetFrameRange(20, 22);
	}
	//nếu nòng súng ở trên cao
	else
	{
		sprite->SetFrameRange(15, 17);
	}
	if(armor > 0)
	{
		if (sprite->GetCurrentFrame() == 1 )
		{
			if (!hadShoot) 
			{
				Canon *canon = new Canon();
				canon->SetPosition(entity->GetPosition().x+10, entity->GetPosition().y+5);
				if (handler->GetLeftTarget())
				{
					canon->Initialize(false, true);
				}	
				else
				{
					canon->Initialize(false, false);
				}
				canon->SetScale(2, 2);
				canon->SetBound(7, 7);
				EntityManager::GetInstance()->AddEntity(canon);
				hadShoot = true;
				armor--;
			}
		}
		else
		{
			hadShoot = false;
		}	
	}
	else
	{
		handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);;
	}
	
}

void NotorBangerShoot::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
