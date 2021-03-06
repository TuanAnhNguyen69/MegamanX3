#include "pch.h"
#include "Shuriken.h"


Shuriken::Shuriken(Player *player) : Enemy(EntityId::Shurikein_ID, player)
{
	turnState = new ShurikenTurn(this, this);
	attack1State = new ShurikenAttack1(this, this);
	attack2State = new ShurikenAttack2(this, this);
	flipState = new ShurikenFlip(this, this);
	moveState = new ShurikenMove(this, this);
	jumpState = new ShurikenJump(this, this);
	dieState = new ShurikenDie(this, this);
}


Shuriken::~Shuriken()
{
	if (turnState)
	{
		delete turnState;
		turnState = nullptr;
	}
	if (attack1State)
	{
		delete attack1State;
		attack1State = nullptr;
	}
	if (attack2State)
	{
		delete attack2State;
		attack2State = nullptr;
	}
	if (flipState)
	{
		delete flipState;
		flipState = nullptr;
	}
	if (moveState)
	{
		delete moveState;
		moveState = nullptr;
	}
	if (jumpState)
	{
		delete jumpState;
		jumpState = nullptr;
	}
	if (dieState)
	{
		delete dieState;
		dieState = nullptr;
	}
}

void Shuriken::Initialize()
{
	this->activeRange = 500;
	this->seen = false;
	this->remove = false;
	this->dead = false;
	this->SetScale(2, 2);
	this->SetBound(50 * 2, 50 * 2);
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"shuriken", 50, 50);
	this->SetPreAction(ShurikenStateHandler::StateName::Jump);
	this->ChangeState(ShurikenStateHandler::StateName::Turn);
	this->HP = Define::SHURIKEN_HP;

	
}

void Shuriken::Update()
{
	if (this->remove)
	{		
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}

	if (this->GetHP() <= 0 && !dead)
	{
		timeStartDie = clock();
		this->ChangeState(ShurikenStateHandler::StateName::Die);
		dead = true;
	}

	if (dead)
	{
		timeDoneDie = clock();
		int numAdd = (timeDoneDie - timeStartDie) % 100;
		if (numAdd == 0)
		{
			explosive = new Explosive();
			explosive->SetPosition(this->GetPosition().x, this->GetPosition().y);
			EntityManager::GetInstance()->AddEntity(explosive);
		}
			
	}

	Enemy::Update();
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
	//default:
	//	currentState = turnState;
	//	currentStateName = Turn;
	//	break;
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
	Enemy::OnCollision(impactor, side, data);
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

void Shuriken::Seen()
{
	seen = true;
}

bool Shuriken::GetSeen()
{
	return this->seen;
}

void Shuriken::SetRemove()
{
	this->remove = true;
}

