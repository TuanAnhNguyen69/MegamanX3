#include "pch.h"
#include "CargoShipDropState.h"


CargoShipDropState::CargoShipDropState(CargoShipStateHandler *handler, Entity *entity) : CargoShipState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "cargo_body",
		0, 0, 1, 256, 88);
	dropLeft = false;
	countCarryArm = 3;
	originalCountCarryArm = 3;
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
	dropLeft = !dropLeft;
	timeStartState = clock();
}

void CargoShipDropState::Update()
{

	if (!hadDrop)
	{
		CarryArm *carryArm = new CarryArm(((Enemy*)entity)->player);
		if (dropLeft)
		{
			carryArm->SetPosition(entity->GetPosition().x - 10, entity->GetPosition().y - 88);
		}
		else
		{
			carryArm->SetPosition(entity->GetPosition().x + 100, entity->GetPosition().y - 88);
		}
		carryArm->SetScale(1.5, 1.5);
		carryArm->SetBound(30 * 1.5, 58 * 1.5);
		carryArm->Initialize();
		EntityManager::GetInstance()->AddEntity(carryArm);

		Sound::getInstance()->loadSound((char*)"sound/shoot_canon.wav", "shoot_canon");
		Sound::getInstance()->play("shoot_canon", false, 1);

		hadDrop = true;
		timeStartUp = clock();
		countCarryArm--;
	}

	if (countCarryArm > 0)
	{
		timeCount = clock();
		if (((float)(timeCount - timeStartState) / 1000) > 2)
		{
			this->Load();
		}
	}
	else
	{
		timeCountAfterDrop = clock();
		float dt = (timeCountAfterDrop - timeStartUp) / 1000;
		if(dt > 4)
		{
			handler->ChangeState(CargoShipStateHandler::StateName::Up);
		}
	}

}

void CargoShipDropState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
