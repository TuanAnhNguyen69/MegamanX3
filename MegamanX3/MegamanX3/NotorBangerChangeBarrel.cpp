#include "pch.h"
#include "NotorBangerChangeBarrel.h"
#include "NotorBanger.h"
#include "Roof.h"
#include "Conveyor.h"


NotorBangerChangeBarrel::NotorBangerChangeBarrel(NotorBangerStateHandler * handler, Entity * entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		5, 7, 5, 50, 50);
}

NotorBangerChangeBarrel::~NotorBangerChangeBarrel()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::ChangeBarrel) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerChangeBarrel::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	sprite->ResetFrame();
	
	isLeft = handler->GetLeftTarget();
	isHigh = handler->GetAboveTarget();

	if (isLeft)
	{
		entity->SetReverse(false);
	}
	else
	{
		entity->SetReverse(true);
	}
	
}

void NotorBangerChangeBarrel::Update()
{
	
	if (handler->GetPreAction() == NotorBangerStateHandler::StateName::Jump)
	{
		if (isHigh)
		{
			//Sau khi bắn nòng súng sẽ ở tên cao
			handler->SetHadChangeHigh(true);
			sprite->SetFrameRange(5, 9);	
		}
		else
		{
			//Sau khi bắn nòng súng sẽ nghiêng
			handler->SetHadChangeHigh(false);
			sprite->SetFrameRange(5, 7);
		}
		if (sprite->IsFinished())
		{
			sprite->ResetFrame();
			handler->ChangeState(NotorBangerStateHandler::StateName::Shoot);
		}
	}
	if (handler->GetPreAction() == NotorBangerStateHandler::StateName::Shoot)
	{
		if (handler->HadChangeHigh())
		{
			sprite->SetFrameRange(10, 14);
			
		}
		else
		{
			sprite->SetFrameRange(12, 14);
		}
		if (sprite->IsFinished())
		{
			//hadStraight = false;
			sprite->ResetFrame();
			handler->ChangeState(NotorBangerStateHandler::StateName::Jump);
		}
	}
	
}

void NotorBangerChangeBarrel::OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if ((impactor->GetEntityId() == EntityId::Platform_ID
		|| impactor->GetEntityId() == EntityId::Thorn_ID))
	{
		//entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		entity->SetVelocity(0, 0);		
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
			entity->SetPosition(entity->GetPosition().x, ((Roof *)impactor)->GetCollidePosition(entity) - entity->GetWidth() / 2);
			entity->SetVelocityY(0);
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
			entity->AddVelocityY(5.0f);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			//if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				
				{
					entity->SetVelocityY(0);
					entity->SetVelocityX(((Conveyor*)(impactor))->GetSpeed());				
					return;
				}
			}
			break;

		}

		}
	}
}
