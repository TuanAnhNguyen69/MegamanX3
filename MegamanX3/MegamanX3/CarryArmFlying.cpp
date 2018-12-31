#include "pch.h"
#include "CarryArmFlying.h"


CarryArmFlying::CarryArmFlying(CarryArmStateHandler *handler, Entity *entity) : CarryArmState(handler, entity)
{
	sprite = new AnimatedSprite(30, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "carry_arm",
		0, 3, 6, 50, 65);
}
CarryArmFlying::~CarryArmFlying()
{
	if (handler->GetCurrentStateName() != CarryArmStateHandler::StateName::Flying) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void CarryArmFlying::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void CarryArmFlying::Update()
{
	if (handler->GetHadDropState()) {
		entity->AddVelocityY(-10.0f);
	}
	else {
		if (!handler->GetLeftTarget())
		{
			entity->SetReverse(true);
			if (!handler->GetAboveTarget()) {
				entity->AddVelocityY(10.0f);
			}
			else {
				handler->ChangeState(CarryArmStateHandler::StateName::Dropping);

			}
		}
		else {
			if (!handler->GetAboveTarget()) {
				entity->AddVelocityY(10.0f);
			}
			else {
				handler->ChangeState(CarryArmStateHandler::StateName::Dropping);

			}
		}
	}


}

void CarryArmFlying::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
