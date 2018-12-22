#include "pch.h"
#include "BlastHornetState.h"


BlastHornetState::BlastHornetState(BlastHornetStateHandler * handler, Entity * entity)
{
}

BlastHornetState::~BlastHornetState()
{
}

void BlastHornetState::Load()
{
}

void BlastHornetState::Update()
{
	if (handler->GetMoveDirection() == BlastHornetStateHandler::MoveDirection::MoveToLeft)
	{
		entity->SetReverse(false);
	}
	else if (handler->GetMoveDirection() == BlastHornetStateHandler::MoveDirection::MoveToRight)
	{
		entity->SetReverse(true);
	}

	//Nếu player ở gần B hơn A
	if (abs(handler->GetPlayerPos().x - handler->GetPointA().x) > abs(handler->GetPlayerPos().x - handler->GetPointB().x))
	{
		isGoToPointA = false;
	}
	//Nếu player ở gần A hơn B
	else
	{
		isGoToPointA = true;
	}
}

void BlastHornetState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
