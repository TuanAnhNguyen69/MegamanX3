#include "pch.h"
#include "CarryArmDie.h"


CarryArmDie::CarryArmDie(CarryArmStateHandler *handler, Entity *entity) : CarryArmState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
		0, 7, 8, 50, 50);
}
CarryArmDie::~CarryArmDie()
{
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}

void CarryArmDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void CarryArmDie::Update()
{
	if (sprite->IsFinished()) {

		entity->SetRemove();
	}
}

void CarryArmDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
