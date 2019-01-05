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
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	timeStartState = clock();
}

void HeadGunnerStanding::Update()
{
	if (!handler->GetIsLeft()) {
		entity->SetReverse(true);
	}
	timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;
	if (dt > 2)
	{
		handler->ChangeState(HeadGunnerStateHandler::StateName::Shoot);
	}
}

void HeadGunnerStanding::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
