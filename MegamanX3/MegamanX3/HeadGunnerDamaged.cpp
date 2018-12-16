#include "pch.h"
#include "HeadGunnerDamaged.h"


HeadGunnerDamaged::HeadGunnerDamaged(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 1, 2, 50, 50);
}
HeadGunnerDamaged::~HeadGunnerDamaged()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Damaged) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerDamaged::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HeadGunnerDamaged::Update()
{
}


void HeadGunnerDamaged::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
