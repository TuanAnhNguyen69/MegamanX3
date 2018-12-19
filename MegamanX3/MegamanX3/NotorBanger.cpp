#include "pch.h"
#include "NotorBanger.h"


NotorBanger::NotorBanger() : Entity(EntityId::NotorBanger_ID)
{	
	standingState = new NotorBangerStanding(this, this);
	shootState = new NotorBangerShoot(this, this);
	jumpState = new NotorBangerJump(this, this);
	damagedState = new NotorBangerDamaged(this, this);
	dieState = new NotorBangerDie(this, this);
}


NotorBanger::~NotorBanger()
{
}

void NotorBanger::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"notor_banger", 50, 50);
	ChangeState(Standing);
}

void NotorBanger::Update()
{
	Entity::Update();
	if (currentState) {
		currentState->Update();
	}
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
	case Shoot:
		currentState = shootState;
		currentStateName = Shoot;
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
	if (this->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (this->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void NotorBanger::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
