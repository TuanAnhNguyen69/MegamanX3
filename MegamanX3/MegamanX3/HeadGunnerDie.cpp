#include "pch.h"
#include "HeadGunnerDie.h"


HeadGunnerDie::HeadGunnerDie(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{

}
HeadGunnerDie::~HeadGunnerDie()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Die) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerDie::Load()
{

}

void HeadGunnerDie::Update()
{

}

void HeadGunnerDie::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}
