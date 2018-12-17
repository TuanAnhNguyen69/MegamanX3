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
	hadStraight = true;
}

void NotorBangerStanding::Update()
{
	handler->SetPreAction(NotorBangerStateHandler::StateName::Jump);
	handler->ChangeState(NotorBangerStateHandler::StateName::ChangeBarrel);
}

void NotorBangerStanding::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}