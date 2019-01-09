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
	isColliBot = false;
	isLeft = handler->GetIsLeft();
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	timeStartState = clock();
	entity->SetReverse(!isLeft);
}

void HeadGunnerStanding::Update()
{
	if (!isColliBot)
	{
		entity->AddVelocityY(10.0f);
	}
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
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{
		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
			entity->SetVelocity(0, 0);
			isColliBot = true;
			break;
		}
		}
	}
}
