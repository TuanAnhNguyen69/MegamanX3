#include "pch.h"
#include "HeadGunnerShoot.h"


HeadGunnerShoot::HeadGunnerShoot(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(5);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 7, 2, 50, 50);
}

HeadGunnerShoot::~HeadGunnerShoot()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Standing) {
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
}

void HeadGunnerShoot::Update()
{
	sprite->SetFrameRange(0, 7);
}

void HeadGunnerShoot::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
