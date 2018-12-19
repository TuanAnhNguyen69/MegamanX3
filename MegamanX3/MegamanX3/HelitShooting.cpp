#include "pch.h"
#include "HelitShooting.h"


HelitShooting::HelitShooting(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit",
		0, 4, 2, 50, 50);
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
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HelitShooting::Update()
{
}

void HelitShooting::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
