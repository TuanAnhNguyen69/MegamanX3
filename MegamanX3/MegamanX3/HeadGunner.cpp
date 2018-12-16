#include "pch.h"
#include "HeadGunner.h"


HeadGunner::HeadGunner() : Entity(EntityId::HeadGunner_ID)
{
	/*
	fireState = nullptr;
	jumpState = nullptr;
	damagedState = nullptr;
	dieState = nullptr;
	fallingState = nullptr;
	*/
	
	standingState = new HeadGunnerStanding(this, this);
	shootState = new HeadGunnerShoot(this, this);
	damagedState = new HeadGunnerDamaged(this, this);
	dieState = new HeadGunnerDie(this, this);
}


HeadGunner::~HeadGunner()
{
}

void HeadGunner::Initialize(int width, int height)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"head_gunner", width, height);
}

void HeadGunner::Update()
{
	Entity::Update();
	if (currentState) {
		currentState->Update();
	}
}

//void HeadGunner::SetPosition(int x, int y)
//{
//	entity->SetPosition(x, y);
//}
//
//D3DXVECTOR3 HeadGunner::GetPosition()
//{
//	return entity->GetPosition();
//}
//
//Entity * HeadGunner::GetEntity()
//{
//	return entity;
//}

HeadGunnerStateHandler::StateName HeadGunner::GetCurrentStateName()
{
	return this->currentStateName;
}

void HeadGunner::ChangeState(StateName stateName)
{
	switch (stateName) {
	case Standing:
		currentState = standingState;
		currentStateName = Standing;
		break;
	case Shoot:
		currentState = shootState;
		currentStateName = Shoot;
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
		currentState = standingState;
		currentStateName = Standing;
		break;
	}
	currentState->Load();
}

HeadGunnerStateHandler::MoveDirection HeadGunner::GetMoveDirection()
{
	if (this->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (this->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void HeadGunner::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void HeadGunner::OnNoCollisionWithBottom()
{
}

//bool HeadGunner::GetAction()
//{
//	return action;
//}
//
//void HeadGunner::SetAction(bool _action)
//{
//	action = _action;
//}
