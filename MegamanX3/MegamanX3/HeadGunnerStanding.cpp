#include "pch.h"
#include "HeadGunnerStanding.h"


HeadGunnerStanding::HeadGunnerStanding(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 0, 4, 50, 50);
}
HeadGunnerStanding::~HeadGunnerStanding()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerStanding::Load()
{
	isLeft = handler->GetIsLeft();
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	timeStartState = clock();
	entity->SetReverse(!isLeft);
}

void HeadGunnerStanding::Update()
{
	timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;

	if (handler->GetAmmoCanon() <= 0)
	{	
		if (dt > 2)
		{
			handler->ResetAmmoCanon();
			handler->ChangeState(HeadGunnerStateHandler::StateName::ShootRocket);
		}
	}
	else
	{
		if (dt > 1)
		{
			handler->SubAmmoCanon();
			handler->ChangeState(HeadGunnerStateHandler::StateName::ShootCanon);
		}
	}
	
}

void HeadGunnerStanding::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
