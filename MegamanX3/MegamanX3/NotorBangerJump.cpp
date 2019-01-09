#include "pch.h"
#include "NotorBangerJump.h"
#include "Conveyor.h"
#include "Roof.h"

NotorBangerJump::NotorBangerJump(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, false);
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
	hadJump = false;
	//Jump
	entity->SetSprite(sprite);
	entity->SetVelocityY(Define::NOTORBANGER_MIN_JUMP_VELOCITY);
	acceleratorX = 20.0f;
	acceleratorY = 20.0f;

	startPos = entity->GetPosition();

	isLeft = handler->GetLeftTarget();

	//Gán giá trị preAction là Jump tiếp tục thực hiện Shoot
	handler->SetPreAction(NotorBangerStateHandler::StateName::Jump);

	//Fall
	//acceleratorX = 8.0f;
}

void NotorBangerJump::Update()
{
	//Jump
	entity->AddVelocityY(acceleratorY);
	if (entity->GetVelocity().y >= 0)
	{
		entity->AddVelocityY(acceleratorY);
	}

	if (isLeft)
	{
		entity->AddVelocityX(-acceleratorX);
		if (entity->GetVelocity().x < 0)
		{
			entity->AddVelocityX(acceleratorX - 5.0f);
		}
	}
	else
	{
		entity->AddVelocityX(acceleratorX);
		if (entity->GetVelocity().x > 0)
		{
			entity->AddVelocityX(-(acceleratorX - 5.0f));
		}
	}

	if (entity->GetPosition().y - startPos.y <= -40)
	{
		hadJump = true;
	}
}

void NotorBangerJump::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID
		|| impactor->GetEntityId() == EntityId::Thorn_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			entity->SetVelocityX(0);
			entity->AddVelocityY(5.0f);
			break;
		}

		case Entity::Right:
		{
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			entity->SetVelocityX(0);
			entity->AddVelocityY(5.0f);
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{
			entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			entity->AddVelocityY(5.0f);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			//if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				if (hadJump)
				{
					entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
					entity->SetVelocity(0, 0);
					sprite->ResetFrame();
					handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
					return;
				}
			}
			break;

		}


		}
	}

	if (impactor->GetEntityId() == EntityId::Roof_ID) {
		switch (side) {
		case Entity::Left:
		{
			if (handler->GetMoveDirection() == PlayerStateHandler::MoveToLeft)
			{
				entity->AddPosition(-5, -5);
			}
			return;
		}

		case Entity::Right:
		{
			if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
			{
				entity->AddPosition(5, -5);
			}
			return;
		}

		case Entity::Top:
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
		{
			//entity->SetPosition(entity->GetPosition().x, ((Roof *)impactor)->GetCollidePosition(entity) - entity->GetWidth() / 2);
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
			entity->SetVelocity(0, 0);
			handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
			return;
		}
		}
	}

	if (impactor->GetEntityId() == EntityId::RightBlueConveyor_ID
		|| impactor->GetEntityId() == EntityId::RightYellowConveyor_ID
		|| impactor->GetEntityId() == EntityId::RightSmallConveyor_ID
		|| impactor->GetEntityId() == EntityId::LeftYellowConveyor_ID
		|| impactor->GetEntityId() == EntityId::LeftYellowConveyor_ID
		|| impactor->GetEntityId() == EntityId::LeftYellowConveyor_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{			
			break;
		}

		case Entity::Right:
		{			
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{
			entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			entity->SetVelocityX(0);
			entity->AddVelocityY(5.0f);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			//if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				if (hadJump)
				{
					entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));					
					entity->SetVelocity(0, 0);
					sprite->ResetFrame();
					handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
					return;
				}
			}
			break;

		}

		}
	}


}