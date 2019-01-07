#include "pch.h"
#include "NotorBangerJump.h"

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
	if (impactor->GetEntityId() != EntityId::Platform_ID)
	{
		return;
	}
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
			if (hadJump)
			{
				entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				entity->SetVelocityY(0);
				sprite->ResetFrame();
				handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
				return;
			}
		}
		break;
		
	}


	}
}