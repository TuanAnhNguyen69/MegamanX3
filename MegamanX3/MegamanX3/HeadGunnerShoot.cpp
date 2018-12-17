#include "pch.h"
#include "HeadGunnerShoot.h"


HeadGunnerShoot::HeadGunnerShoot(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(5, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 7, 4, 50, 50);
}

HeadGunnerShoot::~HeadGunnerShoot()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Shoot) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerShoot::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;
}

void HeadGunnerShoot::Update()
{
	if (sprite->GetCurrentFrame() == 2 || sprite->GetCurrentFrame() == 6)
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
	if (sprite->IsFinished()) {
		handler->ChangeState(HeadGunnerStateHandler::StateName::Standing);
	}
}

void HeadGunnerShoot::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
