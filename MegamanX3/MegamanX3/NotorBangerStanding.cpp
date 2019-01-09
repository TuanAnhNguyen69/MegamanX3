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
}

void NotorBangerStanding::Update()
{
	entity->AddVelocityY(5.0f);
	
}

void NotorBangerStanding::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if ((impactor->GetEntityId() == EntityId::Platform_ID
		|| impactor->GetEntityId() == EntityId::Roof_ID))
	{
		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		entity->SetVelocity(0, 0);
		//handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
		handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);
		return;
	}

}