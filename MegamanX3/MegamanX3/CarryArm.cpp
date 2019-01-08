#include "pch.h"
#include "CarryArm.h"



CarryArm::CarryArm(Player *_player) : Enemy(EntityId::CarryArm_ID, _player)
{
	flyingState = new CarryArmFlying(this, this);
	droppingState = new CarryArmDropping(this, this);
	dieState = new CarryArmDie(this, this);

	player = _player;
}


CarryArm::~CarryArm()
{
	if (flyingState)
	{
		delete flyingState;
		flyingState = nullptr;
	}

	if (droppingState)
	{
		delete droppingState;
		droppingState = nullptr;
	}

	if(dieState)
	{
		delete dieState;
		dieState = nullptr;
	}
}

void CarryArm::Initialize()
{
	this->HP = 5;
	this->damage = 1;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"CarryArm", 50, 65);
	this->ChangeState(CarryArmStateHandler::StateName::Flying);


	this->box = new Box(EntityId::Box_ID, ((Enemy*)this)->player);
	this->box->SetPosition(this->GetPosition().x, this->GetPosition().y + 50);
	this->box->SetScale(1, 1);
	//this->box->SetBound(50 * 1, 50 * 1);
	this->box->Initialize(false);
	EntityManager::GetInstance()->AddEntity(this->box);
}

void CarryArm::Update()
{
	if (this->IsRemove())
	{
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}

	if (this->GetHP() <= 0)
	{
		this->ChangeState(CarryArmStateHandler::StateName::Die);
	}

	//if (IsAction())
	if (this->GetPosition().x > player->GetPosition().x)
	{
		targetIsLeft = true;
	}
	else
	{
		targetIsLeft = false;
	}

	if (player->GetPosition().y < (this->GetPosition().y))
	{
		targetIsAbove = true;
	}
	else
	{
		targetIsAbove = false;
	}

	Enemy::Update();
	if (currentState) {
		currentState->Update();
	}
}

//void CarryArm::SetPosition(int x, int y)
//{
//	entity->SetPosition(x, y);
//}
//
//D3DXVECTOR3 CarryArm::GetPosition()
//{
//	return entity->GetPosition();
//}
//
//Entity * CarryArm::GetEntity()
//{
//	return entity;
//}

CarryArmStateHandler::StateName CarryArm::GetCurrentStateName()
{
	return this->currentStateName;
}

void CarryArm::ChangeState(StateName stateName)
{
	switch (stateName) {
	case Flying:
		currentState = flyingState;
		currentStateName = Flying;
		break;
	case Dropping:
		currentState = droppingState;
		currentStateName = Dropping;
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

CarryArmStateHandler::MoveDirection CarryArm::GetMoveDirection()
{
	if (this->GetVelocity().y > 0) {
		return MoveDirection::MoveToBottom;
	}
	else if (this->GetVelocity().y < 0) {
		return MoveDirection::MoveToTop;
	}
	return MoveDirection::None;
}

void CarryArm::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	Enemy::OnCollision(impactor, side, data);
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void CarryArm::OnNoCollisionWithBottom()
{
}

bool CarryArm::GetLeftTarget()
{
	return targetIsLeft;
}

bool CarryArm::GetAboveTarget()
{
	return targetIsAbove;
}

bool CarryArm::GetHadDropState()
{
	return hadDropState;
}

void CarryArm::SetHadDropState(bool hadShootState)
{
	this->hadDropState = hadShootState;
}


//bool CarryArm::GetAction()
//{
//	return action;
//}
//
//void CarryArm::SetAction(bool _action)
//{
//	action = _action;
//}
