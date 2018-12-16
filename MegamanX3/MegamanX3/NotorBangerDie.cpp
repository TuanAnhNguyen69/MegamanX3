#include "pch.h"
#include "NotorBangerDie.h"

NotorBangerDie::NotorBangerDie(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{

}
NotorBangerDie::~NotorBangerDie()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Die) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerDie::Load()
{
}

void NotorBangerDie::Update()
{
}

void NotorBangerDie::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}