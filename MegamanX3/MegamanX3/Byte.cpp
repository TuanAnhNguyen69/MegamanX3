#include "pch.h"
#include "Byte.h"


Byte::Byte(Player *player) : Enemy(EntityId::Byte_ID, player)
{
	standingState = new ByteStanding(this, this);
	throwState = new ByteThrow(this, this);
	attackState = new ByteAttack(this, this);
	dieState = new ByteDie(this, this);

	this->SetPreAction(ByteStateHandler::StateName::Attack);
}

Byte::~Byte()
{
	if (standingState) {
		delete standingState;
		standingState = nullptr;
	}
}

void Byte::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte", 100, 100);
	this->ChangeState(ByteStateHandler::StateName::Standing);
}


void Byte::Update()
{
	Entity::Update();
	if (currentState)
	{
		currentState->Update();
	}

}

ByteStateHandler::StateName Byte::GetCurrentStateName()
{
	return currentStateName;
}

void Byte::ChangeState(ByteStateHandler::StateName stateName)
{
	switch (stateName) {
	case Standing:
		currentState = standingState;
		currentStateName = Standing;
		break;
	case Die:
		currentState = dieState;
		currentStateName = Die;
		break;
	case Attack:
		currentState = attackState;
		currentStateName = Attack;
		break;
	case Throw:
		currentState = throwState;
		currentStateName = Throw;
		break;
	default:
		currentState = standingState;
		currentStateName = Standing;
		break;
	}
	currentState->Load();
}

ByteStateHandler::MoveDirection Byte::GetMoveDirection()
{
	if (this->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (this->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void Byte::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void Byte::OnNoCollisionWithBottom()
{
}

ByteStateHandler::StateName Byte::GetPreAction()
{
	return preAction;
}

void Byte::SetPreAction(StateName action)
{
	preAction = action;
}

bool Byte::IsFaceLeft()
{
	return isFaceLeft;
}

void Byte::SetFace(bool isLeft)
{
	if (isLeft)
		isFaceLeft = true;
	else
		isFaceLeft = false;
}
