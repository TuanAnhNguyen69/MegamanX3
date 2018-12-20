#include "pch.h"
#include "ShurikenMove.h"


ShurikenMove::ShurikenMove(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(20, 2, true);
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
	entity->SetSprite(sprite);
	//entity->SetVelocity(-Define::SHURIKEN_SPEED_MOVE);
	vMove = D3DXVECTOR3(-Define::SHURIKEN_SPEED_MOVE, 0, 0);
	leaveStartPoint = false;
}

void ShurikenMove::Update()
{
	entity->SetVelocity(vMove.x, vMove.y);
	if (entity->GetPosition().x == startPoint.x && entity->GetPosition().y == startPoint.y && leaveStartPoint)
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Turn);
	}
}

void ShurikenMove::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			leaveStartPoint = true;
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 1, 0);
			//entity->SetVelocity(0, 0);
			vMove.x = 0.0f;
			vMove.y = -Define::SHURIKEN_SPEED_MOVE;
			break;
		}

		case Entity::Right:
		{
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + 1), 0);
			//entity->SetVelocity(0,0);
			vMove.x = 0.0f;
			vMove.y = Define::SHURIKEN_SPEED_MOVE;
			break;
		}

		//case Entity::TopRight: case Entity::TopLeft: 
		case Entity::Top:
		{
			entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top + 1);
			//entity->SetVelocity(0, 0);
			vMove.x = Define::SHURIKEN_SPEED_MOVE;
			vMove.y = 0.0f;
			break;
		}

		//case Entity::BottomRight: case Entity::BottomLeft: 
		case Entity::Bottom:
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
			entity->SetVelocity(0, 0);
			vMove.x = -Define::SHURIKEN_SPEED_MOVE;
			vMove.y = 0.0f;
		}
		}
	}
}
