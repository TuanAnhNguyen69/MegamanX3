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
	EntityManager::GetInstance()->RemoveEntity(entity);
}

void HeadGunnerDie::Update()
{

}

void HeadGunnerDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
