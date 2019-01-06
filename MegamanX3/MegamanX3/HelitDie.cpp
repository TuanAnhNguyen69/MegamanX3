#include "pch.h"
#include "HelitDie.h"


HelitDie::HelitDie(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
		0, 7, 8, 50, 50);
}

HelitDie::~HelitDie()
{
	if (sprite) {
		delete sprite;
	}
}

void HelitDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	
}

void HelitDie::Update()
{

}

void HelitDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
