#include "pch.h"
#include "HelitShooting.h"
#include "HelitRocket.h"


HelitShooting::HelitShooting(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit",
		0, 4, 5, 50, 50);
}

HelitShooting::~HelitShooting()
{
	if (handler->GetCurrentStateName() != HelitStateHandler::StateName::Shooting) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HelitShooting::Load()
{
	hadShoot = false;
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	handler->SetHadShootState(true);
	hadShoot = false;
	armor = 2;
}

void HelitShooting::Update()
{
	if (armor > 0) {
		if (sprite->GetCurrentFrame() == 1) {
			if (!hadShoot) {
				HelitRocket *rocket = new HelitRocket();
				rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y + 22);
				rocket->Initialize(handler->GetLeftTarget());
				rocket->SetScale(2, 2);
				rocket->SetBound(16, 12);
				EntityManager::GetInstance()->AddEntity(rocket);
				hadShoot = true;
				armor--;
			}
		}
		else {
			hadShoot = false;
		}		
	}
	else {
		handler->ChangeState(HelitStateHandler::StateName::Flying);
	}
	
}

void HelitShooting::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
