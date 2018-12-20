#include "pch.h"
#include "ShurikenJump.h"


ShurikenJump::ShurikenJump(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(20, 2, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "shuriken",
		10, 26, 10, 50, 50);
}


ShurikenJump::~ShurikenJump()
{
	if (handler->GetCurrentStateName() != ShurikenStateHandler::StateName::Jump) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ShurikenJump::Load()
{
	handler->SetPreAction(ShurikenStateHandler::StateName::Jump);
	entity->SetSprite(sprite);
	isJumping = false;
	leaveStartPoint = false;
	vJump = D3DXVECTOR3(-Define::SHURIKEN_SPEED_JUMP_X, -Define::SHURIKEN_SPEED_JUMP_Y, 0);
	aJump = D3DXVECTOR3(Define::SHURIKEN_ACCELERATION_JUMP_X, Define::SHURIKEN_ACCELERATION_JUMP_Y, 0);
}

void ShurikenJump::Update()
{
	if (!isJumping)
	{
		entity->SetVelocity(vJump.x, vJump.y);
	}
	else
	{
		isJumping = true;
		entity->AddVelocityX(-aJump.x);
		entity->AddVelocityY(aJump.y);
		if (entity->GetVelocity().x < 0)
		{
			entity->AddVelocityX(aJump.x);
			
		}
		/*else if (entity->GetVelocity().x > 0)
		{
			entity->AddVelocityX(-aJump.x);
		}*/

		if (entity->GetVelocity().y > 0)
		{
			entity->AddVelocityY(Define::SHURIKEN_ACCELERATION_FALL_Y);
		}
	}
	if (entity->GetPosition().x == startPoint.x && entity->GetPosition().y == startPoint.y && leaveStartPoint)
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Turn);
	}
}

void ShurikenJump::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			leaveStartPoint = true;
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 1, 0);
			vJump.x = -vJump.x;
			aJump.x = -aJump.x;
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			isJumping = false;
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		}
		}
	}
}
