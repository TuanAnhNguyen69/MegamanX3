#include "pch.h"
#include "HelitDie.h"


HelitDie::HelitDie(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{

}
HelitDie::~HelitDie()
{
	if (handler->GetCurrentStateName() != HelitStateHandler::StateName::Die) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HelitDie::Load()
{

}

void HelitDie::Update()
{

}

void HelitDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
