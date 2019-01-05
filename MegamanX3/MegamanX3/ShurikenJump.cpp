#include "pch.h"
#include "ShurikenJump.h"


ShurikenJump::ShurikenJump(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(40, 4, true);
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
	hadLeaveStartPoint = false;
	this->startPoint = entity->GetPosition();
	this->wallPoint = D3DXVECTOR3(startPoint.x - 350, startPoint.y, 0);
	isUp = true;
}

void ShurikenJump::Update()
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
	case ShurikenJump::AtStartPoint:
		if (hadLeaveStartPoint)
		{
			handler->ChangeState(ShurikenStateHandler::StateName::Turn);
		}
		else
		{
			JumpTo(startPoint, wallPoint, 20, 100);
		}
		break;
	case ShurikenJump::AtWallPoint:
		hadLeaveStartPoint = true;
		JumpTo(wallPoint, startPoint, 20, 100);
		break;
	case ShurikenJump::Unknow:
		break;
	default:
		break;
	}
}

void ShurikenJump::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	/*if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			hadLeaveStartPoint = true;
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
	}*/
}

void ShurikenJump::JumpTo(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float farJump, float highJump)
{
	if (curPoint.y != desPoint.y)
	{
		return;
	}

	float highPoint = curPoint.y - highJump;

	float size = sqrt(farJump * farJump + highJump * highJump);
	if (curPoint.x < desPoint.x)
	{
		entity->AddVelocityX(farJump / size * Define::SHURIKEN_SPEED_JUMP_X);
	}
	else
	{
		entity->AddVelocityX(farJump / size * -Define::SHURIKEN_SPEED_JUMP_X);
	}
	
	if (entity->GetPosition().y <= highPoint)
	{
		isUp = false;
		entity->SetPositionY(highPoint);
	}
	else if(entity->GetPosition().y >= curPoint.y)
	{
		isUp = true;
		entity->SetPositionY(curPoint.y);
	}

	if (isUp)
	{
		entity->AddVelocityY(highJump / size * -Define::SHURIKEN_SPEED_JUMP_Y);
	}
	else
	{
		entity->AddVelocityY(highJump / size * Define::SHURIKEN_SPEED_JUMP_Y + Define::SHURIKEN_ACCELERATION_FALL_Y);
	}

	if ((entity->GetPosition().x >= desPoint.x && curPoint.x < desPoint.x) ||
		(entity->GetPosition().x <= desPoint.x && curPoint.x > desPoint.x))
	{
		entity->SetPositionX(desPoint.x);
		entity->SetVelocity(0, 0);
		entity->AddVelocityY(Define::SHURIKEN_ACCELERATION_FALL_Y);
	}

	if ((((desPoint.x >= curPoint.x) && (entity->GetPosition().x >= desPoint.x)) ||
		((desPoint.x <= curPoint.x) && (entity->GetPosition().x <= desPoint.x))) &&
		(((desPoint.y >= curPoint.y) && (entity->GetPosition().y >= desPoint.y)) ||
		((desPoint.y <= curPoint.y) && (entity->GetPosition().y <= desPoint.y)))
		)
	{
		entity->SetVelocity(0, 0);
		entity->SetPosition(desPoint.x, desPoint.y);
	}
}


