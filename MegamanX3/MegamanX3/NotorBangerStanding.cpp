#include "pch.h"
#include "NotorBangerStanding.h"

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
	handler->SetPreAction(NotorBangerStateHandler::StateName::Jump);
}

void NotorBangerStanding::Update()
{
	handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);
	//handler->ChangeState(NotorBangerStateHandler::StateName::Jump);
}

void NotorBangerStanding::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	//if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
	{
		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		entity->SetVelocityY(0);
		handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
	}
	return;
}