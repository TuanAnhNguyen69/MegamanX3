#include "pch.h"
#include "NotorBangerJump.h"

NotorBangerJump::NotorBangerJump(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		0, 4, 5, 50, 50);
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
	//Jump
	entity->SetSprite(sprite);
	entity->SetVelocityY(Define::NOTORBANGER_MIN_JUMP_VELOCITY);
	acceleratorX = 20.0f;
	acceleratorY = 20.0f;
	sprite->ResetFrame();

	//Gán giá trị preAction là Jump tiếp tục thực hiện Shoot
	handler->SetPreAction(NotorBangerStateHandler::StateName::Jump);

	//Fall
	//acceleratorX = 8.0f;
}

void NotorBangerJump::Update()
{
	//Jump
	entity->AddVelocityY(acceleratorY);

	if (entity->GetVelocity().y >= 0) {
		//Fall
		acceleratorX = 8.0f;
		entity->AddVelocityY(acceleratorY);
		if (entity->GetVelocity().y > Define::NOTORBANGER_MAX_JUMP_VELOCITY) {
			entity->SetVelocityY(Define::NOTORBANGER_MAX_JUMP_VELOCITY);
		}
		if (entity->GetVelocity().x > -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(-Define::NOTORBANGER_MAX_RUNNING_SPEED);
			}
		}
		return;
	}

	if (handler->GetMoveDirection() == NotorBangerStateHandler::MoveDirection::MoveToLeft) {
		if (entity->GetVelocity().x < 0) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x > 0) {
				entity->SetVelocityX(0);
			}
		}
	}
	/*else if (handler->GetMoveDirection() == NotorBangerStateHandler::MoveDirection::MoveToRight) {
		if (entity->GetVelocity().x > 0) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < 0) {
				entity->SetVelocityX(0);
			}
		}
	}*/

		/*entity->SetReverse(false);
		if (entity->GetVelocity().x < Define::NOTORBANGER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x >= Define::NOTORBANGER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(Define::NOTORBANGER_MAX_RUNNING_SPEED);
			}
		}*/
	
		entity->SetReverse(false);
		if (entity->GetVelocity().x > -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(-Define::NOTORBANGER_MAX_RUNNING_SPEED);
			}
		}


}

void NotorBangerJump::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
		//if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			entity->SetVelocityY(0);
			handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
		}
		return;
		
	}


	}
}