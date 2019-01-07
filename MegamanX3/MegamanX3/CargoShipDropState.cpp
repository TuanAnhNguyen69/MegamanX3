#include "pch.h"
#include "CargoShipDropState.h"


CargoShipDropState::CargoShipDropState(CargoShipStateHandler *handler, Entity *entity) : CargoShipState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "cargo_body",
		0, 0, 1, 256, 88);
}


CargoShipDropState::~CargoShipDropState()
{
	if (handler->GetCurrentStateName() != CargoShipStateHandler::StateName::Down) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void CargoShipDropState::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);

	hadDrop = false;
}

void CargoShipDropState::Update()
{
	if (!hadDrop)
	{
		CarryArm *carryArm = new CarryArm(((Enemy*)entity)->player);
		carryArm->SetPosition(entity->GetPosition().x, entity->GetPosition().y - 88);
		carryArm->SetScale(1.5, 1.5);
		carryArm->SetBound(30 * 1.5, 58 * 1.5);
		carryArm->Initialize();
		EntityManager::GetInstance()->AddEntity(carryArm);
		hadDrop = true;
	}
}

void CargoShipDropState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
