#include "pch.h"
#include "CargoShipDownState.h"


CargoShipDownState::CargoShipDownState(CargoShipStateHandler *handler, Entity *entity) : CargoShipState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "cargo_body",
		0, 0, 1, 256, 88);
}


CargoShipDownState::~CargoShipDownState()
{
	if (handler->GetCurrentStateName() != CargoShipStateHandler::StateName::Down) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void CargoShipDownState::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	startPos = entity->GetPosition();
	desPos = D3DXVECTOR3(startPos.x, startPos.y + 88, 0);
	
}

void CargoShipDownState::Update()
{
	
	entity->GoTo(startPos, desPos, 5.0f);
	if (entity->GetPosition() == desPos)
	{
		if (!handler->sole->HadAlight())
		{
			handler->sole->AddVelocityY(7.0f);
		}
		else
		{
			handler->ChangeState(CargoShipStateHandler::StateName::Drop);
		}
	}
}

void CargoShipDownState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
