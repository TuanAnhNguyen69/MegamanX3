#include "pch.h"
#include "HeadGunnerStanding.h"


HeadGunnerStanding::HeadGunnerStanding(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 1, 2, 50, 50);
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
}

void HeadGunnerStanding::Update()
{
}

void HeadGunnerStanding::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
