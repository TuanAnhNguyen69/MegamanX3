#include "pch.h"
#include "Helit.h"


Helit::Helit() : Entity(EntityId::Helit_ID)
{
	/*
	shootingState = nullptr;
	flyingState = nullptr;
	damagedState = nullptr;
	dieState = nullptr;
	*/

	flyingState = new HelitFlying(this, this);
	shootingState = new HelitShooting(this, this);
	damagedState = new HelitDamaged(this, this);
	dieState = new HelitDie(this, this);
}


Helit::~Helit()
{
}

void Helit::Initialize(int width, int height)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"helit", width, height);
}

void Helit::Update()
{
	Entity::Update();
	if (currentState) {
		currentState->Update();
	}
}

//void Helit::SetPosition(int x, int y)
//{
//	entity->SetPosition(x, y);
//}
//
//D3DXVECTOR3 Helit::GetPosition()
//{
//	return entity->GetPosition();
//}
//
//Entity * Helit::GetEntity()
//{
//	return entity;
//}

HelitStateHandler::StateName Helit::GetCurrentStateName()
{
	return this->currentStateName;
}

void Helit::ChangeState(StateName stateName)
{
	switch (stateName) {
	case Flying:
		currentState = flyingState;
		currentStateName = Flying;
		break;
	case Shooting:
		currentState = shootingState;
		currentStateName = Shooting;
		break;
	case Damaged:
		currentState = damagedState;
		currentStateName = Damaged;
		break;
	case Die:
		currentState = dieState;
		currentStateName = Die;
		break;
	default:
		currentState = flyingState;
		currentStateName = Flying;
		break;
	}
	currentState->Load();
}

HelitStateHandler::MoveDirection Helit::GetMoveDirection()
{
	if (this->GetVelocity().y > 0) {
		return MoveDirection::MoveToBottom;
	}
	else if (this->GetVelocity().y < 0) {
		return MoveDirection::MoveToTop;
	}
	return MoveDirection::None;
}

void Helit::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void Helit::OnNoCollisionWithBottom()
{
}

//bool Helit::GetAction()
//{
//	return action;
//}
//
//void Helit::SetAction(bool _action)
//{
//	action = _action;
//}
