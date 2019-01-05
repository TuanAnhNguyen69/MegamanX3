#include "pch.h"
#include "ShurikenMove.h"


ShurikenMove::ShurikenMove(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(40, 4, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "shuriken",
		0, 9, 10, 50, 50);
}


ShurikenMove::~ShurikenMove()
{
	if (handler->GetCurrentStateName() != ShurikenStateHandler::StateName::Move) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ShurikenMove::Load()
{
	route = Route::Unknow;
	entity->SetSprite(sprite);
	hadLeaveStartPoint = false;
	this->point1 = entity->GetPosition();
	this->point2 = D3DXVECTOR3(point1.x - 350, point1.y, 0);
	this->point3 = D3DXVECTOR3(point1.x - 350, point1.y - 200, 0);
	this->point4 = D3DXVECTOR3(point1.x, point1.y - 200, 0);
	handler->SetPreAction(ShurikenStateHandler::StateName::Move);
}

void ShurikenMove::Update()
{
	if (entity->GetPosition().x == point1.x && entity->GetPosition().y == point1.y)
	{
		route = Route::AtPoint1;
	}
	if (entity->GetPosition().x == point2.x && entity->GetPosition().y == point2.y)
	{
		route = Route::AtPoint2;
	}
	if (entity->GetPosition().x == point3.x && entity->GetPosition().y == point3.y)
	{
		route = Route::AtPoint3;
	}
	if (entity->GetPosition().x == point4.x && entity->GetPosition().y == point4.y)
	{
		route = Route::AtPoint4;
	}

	switch (route)
	{
	case ShurikenMove::AtPoint1:
		if (hadLeaveStartPoint)
		{
			handler->ChangeState(ShurikenStateHandler::StateName::Turn);
		}
		else
		{
			entity->GoTo(point1, point2, Define::SHURIKEN_SPEED_ATTACK);
		}
		break;
	case ShurikenMove::AtPoint2:
		hadLeaveStartPoint = true;
		entity->GoTo(point2, point3, Define::SHURIKEN_SPEED_ATTACK);
		break;
	case ShurikenMove::AtPoint3:
		entity->GoTo(point3, point4, Define::SHURIKEN_SPEED_ATTACK);
		break;
	case ShurikenMove::AtPoint4:
		entity->GoTo(point4, point1, Define::SHURIKEN_SPEED_ATTACK);
		break;
	case ShurikenMove::Unknow:
		break;
	default:
		break;
	}
}

void ShurikenMove::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
	//		vMove.x = 0.0f;
	//		vMove.y = -Define::SHURIKEN_SPEED_MOVE;
	//		break;
	//	}

	//	case Entity::Right:
	//	{
	//		entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + 1), 0);
	//		//entity->SetVelocity(0,0);
	//		vMove.x = 0.0f;
	//		vMove.y = Define::SHURIKEN_SPEED_MOVE;
	//		break;
	//	}

	//	//case Entity::TopRight: case Entity::TopLeft: 
	//	case Entity::Top:
	//	{
	//		entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top + 1);
	//		//entity->SetVelocity(0, 0);
	//		vMove.x = Define::SHURIKEN_SPEED_MOVE;
	//		vMove.y = 0.0f;
	//		break;
	//	}

	//	//case Entity::BottomRight: case Entity::BottomLeft: 
	//	case Entity::Bottom:
	//	{
	//		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
	//		entity->SetVelocity(0, 0);
	//		vMove.x = -Define::SHURIKEN_SPEED_MOVE;
	//		vMove.y = 0.0f;
	//	}
	//	}
	//}
}
