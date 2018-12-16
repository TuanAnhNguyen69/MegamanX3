#include "pch.h"
#include "NotorBangerJump.h"

NotorBangerJump::NotorBangerJump(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		0, 3, 2, 50, 50);
}
NotorBangerJump::~NotorBangerJump()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Jump) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerJump::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocityY(Define::NOTORBANGER_MIN_JUMP_VELOCITY);
	acceleratorX = 14.0f;
	acceleratorY = 15.0f;
	sprite->ResetFrame();
}

void NotorBangerJump::Update()
{
	entity->AddVelocityY(acceleratorY);

	if (entity->GetVelocity().y >= 0) {
		entity->AddVelocityY(acceleratorY);
		if (entity->GetVelocity().y > Define::NOTORBANGER_MAX_JUMP_VELOCITY) {
			entity->SetVelocityY(Define::NOTORBANGER_MAX_JUMP_VELOCITY);
		}

		//Truyền vị trí Megaman để NotorBanger nhảy về hướng đó
		//Nếu bên trái
		if (true)
		{
			entity->SetReverse(false);
			if (entity->GetVelocity().x > -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
				entity->AddVelocityX(-acceleratorX);
				if (entity->GetVelocity().x < -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
					entity->SetVelocityX(-Define::NOTORBANGER_MAX_RUNNING_SPEED);
				}
			}
		}
		//Nếu bên phải
		else
		{
			entity->SetReverse(true);
			if (entity->GetVelocity().x < Define::NOTORBANGER_MAX_RUNNING_SPEED) {
				entity->AddVelocityX(acceleratorX);
				if (entity->GetVelocity().x >= Define::NOTORBANGER_MAX_RUNNING_SPEED) {
					entity->SetVelocityX(Define::NOTORBANGER_MAX_RUNNING_SPEED);
				}
			}
		}
		
	}

	if (handler->GetMoveDirection() == NotorBangerStateHandler::MoveDirection::MoveToLeft) {
		if (entity->GetVelocity().x < 0) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x > 0) {
				entity->SetVelocityX(0);
			}
		}
	}
	else if (handler->GetMoveDirection() == NotorBangerStateHandler::MoveDirection::MoveToRight) {
		if (entity->GetVelocity().x > 0) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < 0) {
				entity->SetVelocityX(0);
			}
		}
	}

	//Vd
	sprite->SetFrameRange(3, 5);

}

void NotorBangerJump::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{
		entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
		entity->SetVelocityX(0);
		break;
	}

	case Entity::Right:
	{
		entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
		entity->SetVelocityX(0);
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
		entity->SetVelocityY(0);
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		entity->SetVelocityY(0);
	}


	default:
		break;
	}
}