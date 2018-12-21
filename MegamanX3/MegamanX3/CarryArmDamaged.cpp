#include "pch.h"
#include "CarryArmDamaged.h"


CarryArmDamaged::CarryArmDamaged(CarryArmStateHandler *handler, Entity *entity) : CarryArmState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "carry_arm",
		0, 1, 2, 50, 50);
}
CarryArmDamaged::~CarryArmDamaged()
{
	if (handler->GetCurrentStateName() != CarryArmStateHandler::StateName::Damaged) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void CarryArmDamaged::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void CarryArmDamaged::Update()
{
}


void CarryArmDamaged::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
