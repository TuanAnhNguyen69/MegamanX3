#include "pch.h"
#include "HelitFlying.h"


HelitFlying::HelitFlying(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit",
		0, 4, 5, 50, 50);
}
HelitFlying::~HelitFlying()
{
	if (handler->GetCurrentStateName() != HelitStateHandler::StateName::Flying) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HelitFlying::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HelitFlying::Update()
{
}

void HelitFlying::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
