#include "pch.h"
#include "BlastHornet.h"


BlastHornet::BlastHornet(Player *player) : Enemy(EntityId::BlastHornet_ID, player)
{
	prepareState = new BlastHornetPrepare(this, this);
	returnState = new BlastHornetReturn(this, this);
	prickState = new BlastHornetPrick(this, this);
	dropState = new BlastHornetDrop(this, this);
	dieState = new BlastHornetDie(this, this);
	flyState = new BlastHornetFly(this, this);

	this->player = player;
}


BlastHornet::~BlastHornet()
{
	if (prepareState)
	{
		delete prepareState;
		prepareState = nullptr;
	}

	if (returnState)
	{
		delete returnState;
		returnState = nullptr;
	}

	if (prickState)
	{
		delete prickState;
		prickState = nullptr;
	}

	if (dropState)
	{
		delete dropState;
		dropState = nullptr;
	}

	if (dieState)
	{
		delete dieState;
		dieState = nullptr;
	}

	if (flyState)
	{
		delete flyState;
		flyState = nullptr;
	}

	Entity::~Entity();
}

void BlastHornet::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"blast_hornet", 100, 100);
	//this->ChangeState(Fly);
	pointA = D3DXVECTOR3(this->GetPosition().x - 50, this->GetPosition().y, 0);
	pointB = D3DXVECTOR3(pointA.x - 350, pointA.y, 0);
	this->SetPreAction(BlastHornetStateHandler::StateName::Drop);
	this->ChangeState(BlastHornetStateHandler::StateName::Return);
	//this->ChangeState(BlastHornetStateHandler::StateName::Fly);
	//this->ChangeState(BlastHornetStateHandler::StateName::Die);
	HP = Define::BLASTHORNET_HP;
}

void BlastHornet::Update()
{
	if (this->IsRemove())
	{
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}

	if (this->GetHP() <= 0)
	{
		this->ChangeState(BlastHornetStateHandler::StateName::Die);
	}

	Entity::Update();
	playerPos = D3DXVECTOR3(player->GetPosition().x, player->GetPosition().y, 0);

	if (currentState)
	{
		currentState->Update();
	}
}

BlastHornetStateHandler::StateName BlastHornet::GetCurrentStateName()
{
	return this->currentStateName;
}

void BlastHornet::ChangeState(StateName stateName)
{
	switch (stateName) {
	case Prepare:
		currentState = prepareState;
		currentStateName = Prepare;
		break;
	case Return:
		currentState = returnState;
		currentStateName = Return;
		break;
	case Prick:
		currentState = prickState;
		currentStateName = Prick;
		break;
	case Drop:
		currentState = dropState;
		currentStateName = Drop;
		break;
	case Fly:
		currentState = flyState;
		currentStateName = Fly;
		break;
	case Die:
		currentState = dieState;
		currentStateName = Die;
		break;
	default:
		currentState = prepareState;
		currentStateName = Prepare;
		break;
	}
	currentState->Load();
}

BlastHornetStateHandler::MoveDirection BlastHornet::GetMoveDirection()
{
	if (this->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (this->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void BlastHornet::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (currentState)
	{
		currentState->OnCollision(impactor, side, data);
	}
}

void BlastHornet::OnNoCollisionWithBottom()
{
}

BlastHornetStateHandler::StateName BlastHornet::GetPreAction()
{
	return this->preAction;
}

void BlastHornet::SetPreAction(StateName action)
{
	preAction = action;
}

D3DXVECTOR3 BlastHornet::GetPlayerPos()
{
	return playerPos;
}

D3DXVECTOR3 BlastHornet::GetPointA()
{
	return pointA;
}

D3DXVECTOR3 BlastHornet::GetPointB()
{
	return pointB;
}

Player * BlastHornet::GetPlayer()
{
	return this->player;
}

int BlastHornet::GetHP()
{
	return this->HP;
}
