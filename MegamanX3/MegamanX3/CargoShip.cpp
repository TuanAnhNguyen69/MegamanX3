#include "pch.h"
#include "CargoShip.h"


CargoShip::CargoShip(Player *player) : Enemy(EntityId::Cargo_ID, player)
{
	this->upState = new CargoShipUpState(this, this);
	this->downState = new CargoShipDownState(this, this);
	this->dropState = new CargoShipDropState(this, this);

	this->player = player;
}


CargoShip::~CargoShip()
{
	if (upState)
	{
		delete upState;
		upState = nullptr;
	}

	if (downState)
	{
		delete downState;
		downState = nullptr;
	}

	if (dropState)
	{
		delete dropState;
		dropState = nullptr;
	}
}

void CargoShip::Initialize(Camera *camera)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"cargo_body", 256, 88);
	this->ChangeState(CargoShipStateHandler::StateName::Down);

	this->originalSolePos = D3DXVECTOR3(this->GetPosition().x + 20, this->GetPosition().y, 0);

	this->sole = new CargoSole();
	this->sole->SetPosition(this->originalSolePos.x, this->originalSolePos.y);
	this->sole->SetScale(2, 2);
	this->sole->SetBound(144 * 2, 88 * 2);
	this->sole->Initialize();
	EntityManager::GetInstance()->AddEntity(this->sole);
}

void CargoShip::Update()
{
	if (this->camera)
	{
		this->sole->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
			SCREEN_HEIGHT / 2 - camera->GetCenter().y);
		this->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
			SCREEN_HEIGHT / 2 - camera->GetCenter().y);
	}
	Enemy::Update();
	if (currentState)
	{
		currentState->Update();
	}
}

CargoShipStateHandler::StateName CargoShip::GetCurrentStateName()
{
	return this->currentStateName;
}

void CargoShip::ChangeState(CargoShipStateHandler::StateName state)
{
	switch (state)
	{
	case CargoShipStateHandler::Up:
		this->currentState = upState;
		this->currentStateName = Up;
		break;
	case CargoShipStateHandler::Down:
		this->currentState = downState;
		this->currentStateName = Down;
		break;
	case CargoShipStateHandler::Drop:
		this->currentState = dropState;
		this->currentStateName = Drop;
		break;
	default:
		break;
	}
	currentState->Load();
}

D3DXVECTOR3 CargoShip::GetOriginalSolePos()
{
	return this->originalSolePos;
}

void CargoShip::SetRemoveSole()
{
	this->sole->SetRemove();
}
