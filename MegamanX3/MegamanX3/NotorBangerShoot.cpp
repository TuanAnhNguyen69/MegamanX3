#include "pch.h"
#include "NotorBangerShoot.h"
#include "NotorBanger.h"


NotorBangerShoot::NotorBangerShoot(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
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
	ammo = 3;
	
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;
	handler->SetPreAction(NotorBangerStateHandler::StateName::Shoot);

	isLeft = handler->GetLeftTarget();
	isHigh = handler->GetAboveTarget();

	if (isHigh)
	{
		sprite->SetFrameRange(15, 17);
	}
	else
	{
		sprite->SetFrameRange(20, 22);
	}
}

void NotorBangerShoot::Update()
{
	//nếu nòng súng không ở trên cao
	

	if (sprite->IsFinished())
	{
		sprite->ResetFrame();
	}

	if(ammo > 0)
	{
		if (sprite->GetCurrentFrame() == 1 )
		{
			if (!hadShoot) 
			{
				Canon *canon = new Canon(((Enemy*)entity)->player);
				if(isLeft)
					canon->SetPosition(entity->GetPosition().x + 10, entity->GetPosition().y + 5);
				else
					canon->SetPosition(entity->GetPosition().x + 10, entity->GetPosition().y - 8);
				canon->Initialize(isHigh, isLeft);
				canon->SetScale(2, 2);
				canon->SetBound(7, 7);
				EntityManager::GetInstance()->AddEntity(canon);
				Sound::getInstance()->loadSound((char*)"sound/shoot_canon.wav", "canon");
				Sound::getInstance()->play("canon", false, 1);

				hadShoot = true;
				ammo--;
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
