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
	startPos = entity->GetPosition();
	desPos = D3DXVECTOR3(startPos.x, startPos.y - 120, 0);
}

void CargoShipUpState::Update()
{
	if (handler->sole)
	{
		if (handler->sole->GetPosition().y > desSolePos.y)
		{
			handler->sole->GoTo(startSolePos, desSolePos, 50.0f);
		}
		else
		{
			handler->SetRemoveSole();
		}
	}
	else
	{
		entity->GoTo(startPos, desPos, 5.0f);
		if (entity->GetPosition() == desPos)
		{
			handler->SetRemove();
		}
	}
}

void CargoShipUpState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
