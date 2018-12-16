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

}

void HeadGunnerShoot::Update()
{
	if (sprite->IsFinished()) {
		handler->ChangeState(HeadGunnerStateHandler::StateName::Standing);
	}
}

void HeadGunnerShoot::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
