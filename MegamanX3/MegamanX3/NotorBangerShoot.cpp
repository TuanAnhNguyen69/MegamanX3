#include "pch.h"
#include "NotorBangerShoot.h"


NotorBangerShoot::NotorBangerShoot(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		10, 19, 5, 50, 50);
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
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;
	handler->SetPreAction(NotorBangerStateHandler::StateName::Shoot);
}

void NotorBangerShoot::Update()
{
	if (hadStraight)
	{
		sprite->SetFrameRange(15, 17);
	}
	else
	{
		sprite->SetFrameRange(10, 12);
	}
	for (int count = 0; count < 3; count++)
	{
		if (sprite->GetCurrentFrame() == 11 || sprite->GetCurrentFrame() == 16)
		{
			if (!hadShoot) {
				HeadGunnerRocket *rocket = new HeadGunnerRocket(true, true);
				rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y - 10);
				rocket->Initialize();
				rocket->SetScale(2, 2);
				rocket->SetBound(25, 9);
				EntityManager::GetInstance()->AddEntity(rocket);
				hadShoot = true;
			}
		}
		else
		{
			hadShoot = false;
		}	
	}
	//if (sprite->IsFinished())
	{
		handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);;
	}
	
}

void NotorBangerShoot::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
