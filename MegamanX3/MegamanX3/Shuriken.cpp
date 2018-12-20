#include "pch.h"
#include "Shuriken.h"


Shuriken::Shuriken(Player *player) : Enemy(EntityId::Shurikein_ID, player)
{
	turnState = new ShurikenState(this, this);
	attack1State = new ShurikenState(this, this);
	attack2State = new ShurikenState(this, this);
	flipState = new ShurikenState(this, this);
	moveState = new ShurikenState(this, this);
	jumpState = new ShurikenState(this, this);
	dieState = new ShurikenState(this, this);
}


Shuriken::~Shuriken()
{

}

void Shuriken::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"shuriken", 50, 50);
	this->ChangeState(Turn);
}

void Shuriken::Update()
{
	Entity::Update();
	if (currentState)
	{
		currentState->Update();
	}
}

ShurikenStateHandler::StateName Shuriken::GetCurrentStateName()
{
	return this->currentStateName;
}

void Shuriken::ChangeState(StateName stateName)
{
	switch (stateName) {
	case Turn:
		currentState = turnState;
		currentStateName = Turn;
		break;
	case Attack1:
		currentState = attack1State;
		currentStateName = Attack1;
		break;
	case Attack2:
		currentState = attack2State;
		currentStateName = Attack2;
		break;
	case Jump:
		currentState = jumpState;
		currentStateName = Jump;
		break;
	case Die:
		currentState = dieState;
		currentStateName = Die;
		break;
	case Move:
		currentState = moveState;
		currentStateName = Move;
		break;
	case Flip:
		currentState = flipState;
		currentStateName = Flip;
		break;
	default:
		currentState = turnState;
		currentStateName = Turn;
		break;
	}
	currentState->Load();
}

ShurikenStateHandler::MoveDirection Shuriken::GetMoveDirection()
{
	if (this->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (this->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void Shuriken::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void Shuriken::OnNoCollisionWithBottom()
{
}

ShurikenStateHandler::StateName Shuriken::GetPreAction()
{
	return this->preAction;
}

void Shuriken::SetPreAction(StateName action)
{
	this->preAction = action;
}


bool Shuriken::GetLeftTarget()
{
	return this->targetIsLeft;
}

bool Shuriken::GetAboveTarget()
{
	return this->targetIsAbout;
}
