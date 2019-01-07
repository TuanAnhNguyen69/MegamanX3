#include "pch.h"
#include "HeadGunnerDie.h"


HeadGunnerDie::HeadGunnerDie(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
		0, 7, 8, 50, 50);
}
HeadGunnerDie::~HeadGunnerDie()
{
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}

void HeadGunnerDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HeadGunnerDie::Update()
{
	if (sprite->IsFinished()) {

		entity->SetRemove();
	}
}

void HeadGunnerDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
