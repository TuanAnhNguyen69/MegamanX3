#include "pch.h"
#include "HeadGunnerShoot.h"


HeadGunnerShoot::HeadGunnerShoot(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	hadShoot = false;
	isRocket = false;
	ammo = 0;
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
	isRocket = true;
	ammo = 5;
}

void HeadGunnerShoot::Update()
{
	if (!handler->GetIsLeft()) {
		entity->SetReverse(true);
		if (sprite->GetCurrentFrame() == 2 || sprite->GetCurrentFrame() == 6)
		{
			if (!hadShoot) {
				HeadGunnerRocket *rocket = new HeadGunnerRocket(false, true);
				rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y - 10);
				rocket->Initialize(false);
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
			/*sprite->SetFrameRange(0, 0);
			if (ammo > 0)
			{
				Canon *canon = new Canon();
				canon->SetPosition(entity->GetPosition().x + 10, entity->GetPosition().y + 5);
				canon->Initialize(false);
				canon->SetScale(2, 2);
				canon->SetBound(9, 9);
				EntityManager::GetInstance()->AddEntity(canon);
				hadShoot = true;
				ammo--;
			}
			else*/
			{
				handler->ChangeState(HeadGunnerStateHandler::StateName::Standing);
			}
		}
	}
	else {
		if (sprite->GetCurrentFrame() == 2 || sprite->GetCurrentFrame() == 6)
		{
			if (!hadShoot) {
				HeadGunnerRocket *rocket = new HeadGunnerRocket(true, true);
				rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y - 10);
				rocket->Initialize(true);
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
			/*sprite->SetFrameRange(0, 0);
			if (ammo > 0)
			{
				Canon *canon = new Canon();
				canon->SetPosition(entity->GetPosition().x + 10, entity->GetPosition().y + 5);
				canon->Initialize(false);
				canon->SetScale(2, 2);
				canon->SetBound(9, 9);
				EntityManager::GetInstance()->AddEntity(canon);
				hadShoot = true;
				ammo--;
			}
			else*/
			{
				handler->ChangeState(HeadGunnerStateHandler::StateName::Standing);
			}
		}
	}
	
}

void HeadGunnerShoot::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
