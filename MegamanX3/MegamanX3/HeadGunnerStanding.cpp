#include "pch.h"
#include "HeadGunnerStanding.h"


HeadGunnerStanding::HeadGunnerStanding(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(10, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 1, 4, 50, 50);
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
	timeChangeState = time(0);
}

void HeadGunnerStanding::Update()
{
	//time_t cout = time(0);
	//if (((cout - timeChangeState) > 4 && (cout - timeChangeState) % 4 == 0))
	//{
		handler->ChangeState(HeadGunnerStateHandler::StateName::Shoot);
		//return;
	//}
}

void HeadGunnerStanding::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
