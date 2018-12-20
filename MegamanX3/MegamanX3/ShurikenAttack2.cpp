#include "pch.h"
#include "ShurikenAttack2.h"


ShurikenAttack2::ShurikenAttack2(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(20, 2, true);
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
	vAttack = D3DXVECTOR3(-Define::SHURIKEN_SPEED_ATTACK, 0, 0);
	leaveStartPoint = false;
}

void ShurikenAttack2::Update()
{
	entity->SetVelocity(vAttack.x, vAttack.y);
	if (entity->GetPosition().x == startPoint.x && entity->GetPosition().y == startPoint.y && leaveStartPoint)
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Turn);
	}
}

void ShurikenAttack2::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
		}
	}
}
