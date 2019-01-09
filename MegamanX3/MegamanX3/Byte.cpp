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

	if (throwState)
	{
		delete throwState;
		throwState = nullptr;
	}

	if (attackState)
	{
		delete attackState;
		attackState = nullptr;
	}

	if (dieState)
	{
		delete dieState;
		dieState = nullptr;
	}
}

void Byte::Initialize()
{
	seen = false;
	dead = false;
	this->damage = 1;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte", 100, 100);
	this->SetFace(true);
	this->ChangeState(ByteStateHandler::StateName::Standing);
	this->HP = Define::BYTE_HP;
}


void Byte::Update()
{
	if (this->IsRemove())
	{
		Sound::getInstance()->loadSound((char*)"sound/explosion.wav", "explosion_die");
		Sound::getInstance()->play("explosion_die", false, 5);
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}

	if (this->GetHP() <= 0 && !dead)
	{
		timeStartDie = clock();
		this->ChangeState(ByteStateHandler::StateName::Die);
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
	Enemy::OnCollision(impactor, side, data);
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
	isFaceLeft = isLeft;
}

void Byte::Seen()
{
	this->seen = true;
}

bool Byte::GetSeen()
{
	return this->seen;
}
