#include "pch.h"
#include "CarryArmDie.h"


CarryArmDie::CarryArmDie(CarryArmStateHandler *handler, Entity *entity) : CarryArmState(handler, entity)
{

}
CarryArmDie::~CarryArmDie()
{
	if (handler->GetCurrentStateName() != CarryArmStateHandler::StateName::Die) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void CarryArmDie::Load()
{

}

void CarryArmDie::Update()
{

}

void CarryArmDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
