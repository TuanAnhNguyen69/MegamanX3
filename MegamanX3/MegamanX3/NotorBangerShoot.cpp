#include "pch.h"
#include "NotorBangerShoot.h"
#include "NotorBanger.h"
#include "Conveyor.h"
#include "Roof.h"

NotorBangerShoot::NotorBangerShoot(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		15, 24, 5, 50, 50);
}

NotorBangerShoot::~NotorBangerShoot()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Shoot) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerShoot::Load()
{
	ammo = 3;

	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;
	handler->SetPreAction(NotorBangerStateHandler::StateName::Shoot);

	isLeft = handler->GetLeftTarget();
	isHigh = handler->GetAboveTarget();

	if (isHigh)
	{
		sprite->SetFrameRange(15, 17);
	}
	else
	{
		sprite->SetFrameRange(20, 22);
	}
}

void NotorBangerShoot::Update()
{
	//nếu nòng súng không ở trên cao


	if (sprite->IsFinished())
	{
		sprite->ResetFrame();
	}

	if (ammo > 0)
	{
		if (sprite->GetCurrentFrame() == 1)
		{
			if (!hadShoot)
			{
				Canon *canon = new Canon(((Enemy*)entity)->player);
				if (isLeft)
					canon->SetPosition(entity->GetPosition().x + 10, entity->GetPosition().y + 5);
				else
					canon->SetPosition(entity->GetPosition().x + 10, entity->GetPosition().y - 8);
				canon->Initialize(isHigh, isLeft);
				canon->SetScale(2, 2);
				canon->SetBound(7, 7);
				EntityManager::GetInstance()->AddEntity(canon);
				Sound::getInstance()->play("shoot_canon", false, 1);

				hadShoot = true;
				ammo--;
			}
		}
		else
		{
			hadShoot = false;
		}
	}
	else
	{
		handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);;
	}

}

void NotorBangerShoot::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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

				entity->SetVelocityY(0);
				entity->SetVelocityX(((Conveyor*)(impactor))->GetSpeed());
				return;

			}
			break;

		}

		}
	}
}
