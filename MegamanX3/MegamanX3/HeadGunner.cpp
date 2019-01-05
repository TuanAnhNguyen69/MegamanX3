#include "pch.h"
#include "HeadGunner.h"
#include <ctime>


HeadGunner::HeadGunner(Player * player) : Enemy(EntityId::HeadGunner_ID, player)
{
	standingState = new HeadGunnerStanding(this, this);
	shootState = new HeadGunnerShoot(this, this);
	damagedState = new HeadGunnerDamaged(this, this);
	dieState = new HeadGunnerDie(this, this);
}


HeadGunner::~HeadGunner()
{
	if (standingState) {
		delete standingState;
		standingState = nullptr;
	}
}

void HeadGunner::Initialize( bool isLeft)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"head_gunner", 50, 50);
	this->isLeft = isLeft;
	this->ChangeState(HeadGunnerStateHandler::StateName::Standing);
}

void HeadGunner::Update()
{
	if (currentState) {
			currentState->Update();
	}
	Entity::Update();
}

HeadGunnerStateHandler::StateName HeadGunner::GetCurrentStateName()
{
	return this->currentStateName;
}

void HeadGunner::ChangeState(HeadGunnerStateHandler::StateName stateName)
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

void HeadGunner::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void HeadGunner::OnNoCollisionWithBottom()
{
}

bool HeadGunner::GetIsLeft()
{
	return isLeft;
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
