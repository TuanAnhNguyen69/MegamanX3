#include "pch.h"
#include "ShurikenAttack1.h"


ShurikenAttack1::ShurikenAttack1(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(20, 2, true);
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
	entity->SetSprite(sprite);
	vAttack = D3DXVECTOR3(-Define::SHURIKEN_SPEED_ATTACK, 0, 0);
	leaveStartPoint = false;
	passJumpPoint = false;
}

void ShurikenAttack1::Update()
{
	entity->SetVelocity(vAttack.x, vAttack.y);
	if (entity->GetPosition().x == jumpPoint.x && entity->GetPosition().y == jumpPoint.y && !passJumpPoint)
	{
			vAttack.y = -Define::SHURIKEN_SPEED_ATTACK;
	}
	if (entity->GetPosition().x == startPoint.x && entity->GetPosition().y == startPoint.y && leaveStartPoint)
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Turn);
	}
}

void ShurikenAttack1::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
			vAttack.x = Define::SHURIKEN_SPEED_MOVE;
			vAttack.y = Define::SHURIKEN_SPEED_MOVE;
			break;
		}

		//case Entity::BottomRight: case Entity::BottomLeft: 
		case Entity::Bottom:
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
			entity->SetVelocity(0, 0);
			vAttack.x = Define::SHURIKEN_SPEED_MOVE;
			vAttack.y = 0.0f;
		}
		}
	}
}
