#include "pch.h"
#include "CargoShipUpState.h"


CargoShipUpState::CargoShipUpState(CargoShipStateHandler *handler, Entity *entity) : CargoShipState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "cargo_body",
		0, 0, 1, 256, 88);
}


CargoShipUpState::~CargoShipUpState()
{
	if (handler->GetCurrentStateName() != CargoShipStateHandler::StateName::Up) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void CargoShipUpState::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	startSolePos = handler->sole->GetPosition();
	desSolePos = handler->GetOriginalSolePos();
}

void CargoShipUpState::Update()
{
	if (handler->sole->GetPosition().y > desSolePos.y)
	{
		handler->sole->GoTo(startSolePos, desSolePos, 20.0f);
	}
	else
	{
		entity->AddVelocityY(-5.0f);
		handler->SetRemoveSole();
	}
}

void CargoShipUpState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
