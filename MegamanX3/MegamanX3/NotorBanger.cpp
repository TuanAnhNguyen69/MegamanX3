#include "pch.h"
#include "NotorBanger.h"


NotorBanger::NotorBanger() 
{
	entity = nullptr;
	fireState = nullptr;
	jumpState = nullptr;
	damagedState = nullptr;
	dieState = nullptr;
}


NotorBanger::~NotorBanger()
{
}

void NotorBanger::Initialize(LPDIRECT3DDEVICE9 device, Camera * camera)
{
	this->camera = camera;

	entity = EntityManager::GetInstance()->AddEntity(EntityId::NotorBanger);
	entity->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	entity->SetScale(2, 2);

	standingState = new NotorBangerStanding(this, entity);
	fireState = new NotorBangerFire(this, entity);
	jumpState = new NotorBangerJump(this, entity);
	damagedState = new NotorBangerDamaged(this, entity);
	dieState = new NotorBangerDie(this, entity);

}

void NotorBanger::Update()
{
	if (currentState) {
		currentState->Update();
	}
}

void NotorBanger::SetPosition(int x, int y)
{
}

D3DXVECTOR3 NotorBanger::GetPosition()
{
	return D3DXVECTOR3();
}

Entity * NotorBanger::GetEntity()
{
	return nullptr;
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
	}
}

NotorBangerStateHandler::MoveDirection NotorBanger::GetMoveDirection()
{
	if (entity->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (entity->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void NotorBanger::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

void NotorBanger::OnNoCollisionWithBottom()
{
}
