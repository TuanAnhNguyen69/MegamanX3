#include "pch.h"
#include "NotorBanger.h"


NotorBanger::NotorBanger(Player *_player) : Enemy(EntityId::NotorBanger_ID, _player)
{	
	standingState = new NotorBangerStanding(this, this);
	shootState = new NotorBangerShoot(this, this);
	jumpState = new NotorBangerJump(this, this);
	damagedState = new NotorBangerDamaged(this, this);
	dieState = new NotorBangerDie(this, this);
	changeBarrelState = new NotorBangerChangeBarrel(this, this);
	player = _player;
}


NotorBanger::~NotorBanger()
{
	if (standingState) {
		delete standingState;
		standingState = nullptr;
	}
}

void NotorBanger::Initialize()
{
	this->HP = 5;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"notor_banger", 50, 50);
	this->SetPreAction(NotorBangerStateHandler::StateName::Jump);
	this->ChangeState(NotorBangerStateHandler::StateName::Standing);
}

void NotorBanger::Update()
{
	if (this->IsRemove())
	{
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}

	if (this->GetHP() <= 0)
	{
		this->ChangeState(NotorBangerStateHandler::StateName::Die);
	}

	if (this->GetPosition().x > player->GetPosition().x)
	{
		targetIsLeft = true;
	}
	else
	{
		targetIsLeft = false;
	}

	if (player->GetPosition().y <= -(this->GetPosition().y - this->GetHeight() * 2))
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
	/*case Falling:
		currentState = fallingState;
		currentStateName = Falling;
		break;*/
	case ChangeBarrel:
		currentState = changeBarrelState;
		currentStateName = ChangeBarrel;
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

NotorBangerStateHandler::StateName NotorBanger::GetPreAction()
{
	return preAction;
}

void NotorBanger::SetPreAction(StateName action)
{
	preAction = action;
}

void NotorBanger::SetBarrelState(BarrelState bt)
{
	barrelState = bt;
}

NotorBangerStateHandler::BarrelState NotorBanger::GetBarrelState()
{
	return barrelState;
}

bool NotorBanger::GetLeftTarget()
{
	return targetIsLeft;
}

bool NotorBanger::GetAboveTarget()
{
	return targetIsAbove;
}

D3DXVECTOR3 NotorBanger::GetPlayerPos()
{
	return this->player->GetPosition();
}

bool NotorBanger::HadChangeHigh()
{
	return hadChangeHigh;
}

void NotorBanger::SetHadChangeHigh(bool hadChangeHigh)
{
	this->hadChangeHigh = hadChangeHigh;
}
