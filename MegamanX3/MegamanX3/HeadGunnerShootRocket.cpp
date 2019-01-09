#include "pch.h"
#include "HeadGunnerShootRocket.h"


HeadGunnerShootRocket::HeadGunnerShootRocket(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 7, 4, 50, 50);
}


HeadGunnerShootRocket::~HeadGunnerShootRocket()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::ShootRocket) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerShootRocket::Load()
{
	isLeft = handler->GetIsLeft();
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;

	entity->SetReverse(!isLeft);
}

void HeadGunnerShootRocket::Update()
{
	if (sprite->GetCurrentFrame() == 2 || sprite->GetCurrentFrame() == 6)
	{
		if (!hadShoot) 
		{
			HeadGunnerRocket *rocket = new HeadGunnerRocket(((Enemy*)entity)->player);
			rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y - 10);
			rocket->Initialize(isLeft);
			rocket->SetScale(2, 2);
			rocket->SetBound(25, 9);
			EntityManager::GetInstance()->AddEntity(rocket);		
			Sound::getInstance()->play("shoot_rocket", false, 1);
			hadShoot = true;
		}
	}
	else
	{
		hadShoot = false;
	}
	if (sprite->IsFinished()) 
	{
		sprite->ResetFrame();
		handler->ChangeState(HeadGunnerStateHandler::StateName::Standing);
	}
}

void HeadGunnerShootRocket::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
