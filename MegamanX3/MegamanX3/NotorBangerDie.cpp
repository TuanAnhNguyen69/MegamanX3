#include "pch.h"
#include "NotorBangerDie.h"

NotorBangerDie::NotorBangerDie(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
		0, 7, 8, 50, 50);
}
NotorBangerDie::~NotorBangerDie()
{
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}

void NotorBangerDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void NotorBangerDie::Update()
{
	if (sprite->IsFinished()) {

		entity->SetRemove();
	}
}

void NotorBangerDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}