#include "pch.h"
#include "NotorBanger.h"


NotorBanger::NotorBanger(float positionX, float positionY, float scaleX, float scaleY)
{
	/*
	fireState = nullptr;
	jumpState = nullptr;
	damagedState = nullptr;
	dieState = nullptr;
	fallingState = nullptr;
	*/

	entity = EntityManager::GetInstance()->AddEntity(EntityId::NotorBanger_ID);
	entity->SetPosition(positionX, positionX);
	entity->SetScale(scaleX, scaleY);

	standingState = new NotorBangerStanding(this, entity);
	fireState = new NotorBangerFire(this, entity);
	jumpState = new NotorBangerJump(this, entity);
	damagedState = new NotorBangerDamaged(this, entity);
	dieState = new NotorBangerDie(this, entity);
	fallingState = new NotorBangerFalling(this, entity);
}


NotorBanger::~NotorBanger()
{
}

void NotorBanger::Initialize()
{

}

void NotorBanger::Update()
{
	if (currentState) {
		currentState->Update();
	}
}

void NotorBanger::SetPosition(int x, int y)
{
	entity->SetPosition(x, y);
}

D3DXVECTOR3 NotorBanger::GetPosition()
{
	return entity->GetPosition();
}

Entity * NotorBanger::GetEntity()
{
	return entity;
}

NotorBangerStateHandler::StateName NotorBanger::GetCurrentStateName()
{
	return this->currentStateName;
}

void NotorBanger::ChangeState(StateName stateName)
{
	switch (stateName) {
	case Standing:
		currentState = standingState;
		currentStateName = Standing;
		break;
	case Fire:
		currentState = fireState;
		currentStateName = Fire;
		break;
	case Jump:
		currentState = jumpState;
		currentStateName = Jump;
		break;
	case Damaged:
		currentState = damagedState;
		currentStateName = Damaged;
		break;
	case Die:
		currentState = dieState;
		currentStateName = Die;
		break;
	case Falling:
		currentState = fallingState;
		currentStateName = Falling;
		break;
	default:
		currentState = standingState;
		currentStateName = Standing;
		break;
	}
	currentState->Load();
}

NotorBangerStateHandler::MoveDirection NotorBanger::GetMoveDirection()
{
	if (entity->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (entity->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void NotorBanger::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void NotorBanger::OnNoCollisionWithBottom()
{
}

bool NotorBanger::GetAction()
{
	return action;
}

void NotorBanger::SetAction(bool _action)
{
	action = _action;
}
