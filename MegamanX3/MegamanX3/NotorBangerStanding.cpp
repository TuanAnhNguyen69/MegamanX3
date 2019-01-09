#include "pch.h"
#include "NotorBangerStanding.h"
#include "Roof.h"
#include "Conveyor.h"

NotorBangerStanding::NotorBangerStanding(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		0, 0, 5, 50, 50);
}
NotorBangerStanding::~NotorBangerStanding()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerStanding::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void NotorBangerStanding::Update()
{
	entity->AddVelocityY(5.0f);

}

void NotorBangerStanding::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if ((impactor->GetEntityId() == EntityId::Platform_ID
		|| impactor->GetEntityId() == EntityId::Thorn_ID))
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
			
				entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				entity->SetVelocity(0, 0);
				handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);
				return;
			
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
			entity->SetPosition(entity->GetPosition().x, ((Roof *)impactor)->GetCollidePosition(entity) - entity->GetWidth() / 2 + 20);
			entity->SetVelocityY(0);
			handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);
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

				entity->SetVelocityY(0);
				entity->SetVelocityX(((Conveyor*)(impactor))->GetSpeed() * 4);
				handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);
				return;

			}
			break;

		}

		}
	}
}