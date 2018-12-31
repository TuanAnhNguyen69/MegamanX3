#include "pch.h"
#include "Helit.h"



Helit::Helit(Player *_player) : Enemy(EntityId::Helit_ID, _player)
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

	player = _player;
}


Helit::~Helit()
{
}

void Helit::Initialize()
{
	hp = 100;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"helit", 50, 50);
	this->ChangeState(HelitStateHandler::StateName::Flying);
}

void Helit::Update()
{
	//if (IsAction())
	
	if (this->GetPosition().x > player->GetPosition().x)
	{
		targetIsLeft = true;
	}
	else
	{
		targetIsLeft = false;
	}

	if (player->GetPosition().y  < (this->GetPosition().y ))
	{
		targetIsAbove = true;
	}
	else
	{
		targetIsAbove = false;
	}

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

bool Helit::GetLeftTarget()
{
	return targetIsLeft;
}

bool Helit::GetAboveTarget()
{
	return targetIsAbove;
}

bool Helit::GetHadShootState()
{
	return hadShootState;
}

void Helit::SetHadShootState(bool hadShootState)
{
	this->hadShootState = hadShootState;
}

int Helit::GetHP()
{
	return hp;
}

void Helit::SetHP(int hp)
{
	this->hp = hp;
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
