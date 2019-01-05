#include "pch.h"
#include "ShurikenAttack2.h"


ShurikenAttack2::ShurikenAttack2(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(40, 4, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "shuriken",
		0, 9, 10, 50, 50);
}


ShurikenAttack2::~ShurikenAttack2()
{
	if (handler->GetCurrentStateName() != ShurikenStateHandler::StateName::Attack2) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ShurikenAttack2::Load()
{
	entity->SetSprite(sprite);
	hadLeaveStartPoint = false;
	this->startPoint = entity->GetPosition();
	this->wallPoint = D3DXVECTOR3(startPoint.x - 350, startPoint.y, 0);
	handler->SetPreAction(ShurikenStateHandler::StateName::Attack2);
}

void ShurikenAttack2::Update()
{
	if (entity->GetPosition().x == startPoint.x && entity->GetPosition().y == startPoint.y)
	{
		route = Route::AtStartPoint;
	}
	if (entity->GetPosition().x == wallPoint.x && entity->GetPosition().y == wallPoint.y)
	{
		route = Route::AtWallPoint;
	}

	switch (route)
	{
	case ShurikenAttack2::AtStartPoint:
		if (hadLeaveStartPoint)
		{
			handler->ChangeState(ShurikenStateHandler::StateName::Turn);
		}
		else
		{
			entity->GoTo(startPoint, wallPoint, Define::SHURIKEN_SPEED_ATTACK);
		}
		break;
	case ShurikenAttack2::AtWallPoint:
		hadLeaveStartPoint = true;
		entity->GoTo(wallPoint, startPoint, Define::SHURIKEN_SPEED_ATTACK);
		break;
	case ShurikenAttack2::Unknow:
		break;
	default:
		break;
	}
}

void ShurikenAttack2::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	//if (impactor->GetEntityId() == EntityId::Platform_ID)
	//{
	//	switch (side)
	//	{

	//	case Entity::Left:
	//	{
	//		leaveStartPoint = true;
	//		entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 1, 0);
	//		//entity->SetVelocity(0, 0);
	//		vAttack.x = Define::SHURIKEN_SPEED_MOVE;
	//		vAttack.y = Define::SHURIKEN_SPEED_MOVE;
	//		break;
	//	}
	//	}
	//}
}
