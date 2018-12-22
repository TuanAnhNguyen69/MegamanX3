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

}

void BlastHornet::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"blast_hornet", 100, 100);
	this->ChangeState(Fly);
	pointA = D3DXVECTOR3(this->GetPosition().x, this->GetPosition().y, 0);
	pointB = D3DXVECTOR3(pointA.x - 800, pointA.y, 0);
}

void BlastHornet::Update()
{
	Entity::Update();
	playerPos = D3DXVECTOR3(player->GetPosition().x, player->GetPosition().y, 0);
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
