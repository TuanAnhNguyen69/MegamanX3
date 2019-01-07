#include "pch.h"
#include "ShurikenAttack1.h"


ShurikenAttack1::ShurikenAttack1(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(40, 4, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "shuriken",
		0, 9, 10, 50, 50);
}


ShurikenAttack1::~ShurikenAttack1()
{
	if (handler->GetCurrentStateName() != ShurikenStateHandler::StateName::Attack1) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ShurikenAttack1::Load()
{
	route = Route::Unknow;
	entity->SetSprite(sprite);
	this->startPoint = entity->GetPosition();
	this->jumpPoint = D3DXVECTOR3(startPoint.x - 200, startPoint.y, 0);
	this->wallPoint = D3DXVECTOR3(startPoint.x - 350, startPoint.y - 100, 0);
	hadLeaveStartPoint = false;
	hadPassJumpPoint = false;
	handler->SetPreAction(ShurikenStateHandler::StateName::Attack1);
}

void ShurikenAttack1::Update()
{
	if (entity->GetPosition().x == startPoint.x && entity->GetPosition().y == startPoint.y)
	{
		route = Route::AtStartPoint;
	}
	if (entity->GetPosition().x == jumpPoint.x && entity->GetPosition().y == jumpPoint.y)
	{
		route = Route::AtJumpPoint;
	}
	if (entity->GetPosition().x == wallPoint.x && entity->GetPosition().y == wallPoint.y)
	{
		route = Route::AtWallPoint;
	}

	switch (route)
	{
	case ShurikenAttack1::AtStartPoint:
		if (!hadLeaveStartPoint)
		{
			entity->GoTo(startPoint, jumpPoint, Define::SHURIKEN_SPEED_ATTACK);
		}
		else
		{
			handler->ChangeState(ShurikenStateHandler::StateName::Turn);
		}
		break;
	case ShurikenAttack1::AtJumpPoint:
		if (!hadPassJumpPoint)
		{
			hadLeaveStartPoint = true;
			entity->GoTo(jumpPoint, wallPoint, Define::SHURIKEN_SPEED_ATTACK + Define::SHURIKEN_ACCELERATION_ATTACK);
		}
		else
		{
			entity->GoTo(jumpPoint, startPoint, Define::SHURIKEN_SPEED_ATTACK + Define::SHURIKEN_ACCELERATION_ATTACK);
		}
		break;
	case ShurikenAttack1::AtWallPoint:
		hadPassJumpPoint = true;
		entity->GoTo(wallPoint, jumpPoint, Define::SHURIKEN_SPEED_ATTACK);
		break;
	case ShurikenAttack1::Unknow:
		break;
	default:
		break;
	}

}

void ShurikenAttack1::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	//if (impactor->GetEntityId() == EntityId::Platform_ID)
	//{
	//	switch (side)
	//	{

	//	case Entity::Left:
	//	{
	//		entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 1, 0);
	//		//entity->SetVelocity(0, 0);
	//		vAttack.x = Define::SHURIKEN_SPEED_MOVE;
	//		vAttack.y = Define::SHURIKEN_SPEED_MOVE;
	//		break;
	//	}

	//	//case Entity::BottomRight: case Entity::BottomLeft: 
	//	case Entity::Bottom:
	//	{
	//		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
	//		entity->SetVelocity(0, 0);
	//		vAttack.x = Define::SHURIKEN_SPEED_MOVE;
	//		vAttack.y = 0.0f;
	//	}
	//	}
	//}
}
