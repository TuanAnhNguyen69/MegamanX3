#include "pch.h"
#include "HeadGunner.h"
#include <ctime>


HeadGunner::HeadGunner(Player * player, EntityId id) : Enemy(id, player)
{
	standingState = new HeadGunnerStanding(this, this);
	shootRocketState = new HeadGunnerShootRocket(this, this);
	shootCanonState = new HeadGunnerShootCanon(this, this);
	dieState = new HeadGunnerDie(this, this);
}


HeadGunner::~HeadGunner()
{
	if (standingState) {
		delete standingState;
		standingState = nullptr;
	}

	if (shootCanonState)
	{
		delete shootCanonState;
		shootCanonState = nullptr;
	}

	if (shootRocketState)
	{
		delete shootRocketState;
		shootRocketState = nullptr;
	}

	if (dieState)
	{
		delete dieState;
		dieState = nullptr;
	}

	Entity::~Entity();
}

void HeadGunner::Initialize( bool isLeft)
{
	this->HP = 5;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"head_gunner", 50, 50);
	this->isLeft = isLeft;
	ammoCanon = 0;
	this->ChangeState(HeadGunnerStateHandler::StateName::Standing);
}

void HeadGunner::Update()
{
	if (this->IsRemove())
	{
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}

	if (this->HP <= 0)
	{
		this->ChangeState(HeadGunnerStateHandler::StateName::Die);
	}
	Entity::Update();
	if (currentState) {
			currentState->Update();
	}
	
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
	case Die:
		currentState = dieState;
		currentStateName = Die;
		break;
	case ShootRocket:
		currentState = shootRocketState;
		currentStateName = ShootRocket;
		break;
	case ShootCanon:
		currentState = shootCanonState;
		currentStateName = ShootCanon;
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
	Enemy::OnCollision(impactor, side, data);
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void HeadGunner::OnNoCollisionWithBottom()
{
}

int HeadGunner::GetAmmoCanon()
{
	return ammoCanon;
}

void HeadGunner::ResetAmmoCanon()
{
	ammoCanon = 2;
}

void HeadGunner::SubAmmoCanon()
{
	ammoCanon--;
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
