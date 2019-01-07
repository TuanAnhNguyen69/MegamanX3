#include "pch.h"
#include "BlastHornetState.h"


BlastHornetState::BlastHornetState(BlastHornetStateHandler * handler, Entity * entity)
{
	this->handler = handler;
	this->entity = entity;
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
}

void BlastHornetState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}

float BlastHornetState::UCLN(float a, float b)
{
	if (a == 0.0 || b == 0.0)
	{
		return 1.0;
	}
	while (a != b)
	{
		if (a > b)
		{
			a -= b;
		}
		else
		{
			b -= a;
		}
	}
	return a;

}

//void BlastHornetState::GoTo(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed)
//{
//	D3DXVECTOR3 moveVector;
//
//	moveVector = D3DXVECTOR3(desPoint.x - curPoint.x, desPoint.y - curPoint.y, 0);
//
//	float speedVector = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
//
//	entity->AddVelocityX(moveVector.x / speedVector * speed);
//	entity->AddVelocityY(moveVector.y / speedVector * speed);
//
//	if ((((desPoint.x >= curPoint.x) && (entity->GetPosition().x >= desPoint.x)) ||
//		((desPoint.x <= curPoint.x) && (entity->GetPosition().x <= desPoint.x))) &&
//		(((desPoint.y >= curPoint.y) && (entity->GetPosition().y >= desPoint.y)) ||
//		((desPoint.y <= curPoint.y) && (entity->GetPosition().y <= desPoint.y)))
//		)
//	{
//		entity->SetVelocity(0, 0);
//		entity->SetPosition(desPoint.x, desPoint.y);
//	}
//}
//
//void BlastHornetState::GoOn(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed)
//{
//	D3DXVECTOR3 moveVector;
//
//	moveVector = D3DXVECTOR3(desPoint.x - curPoint.x, desPoint.y - curPoint.y, 0);
//
//	float speedVector = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
//
//	entity->AddVelocityX(moveVector.x / speedVector * speed);
//	entity->AddVelocityY(moveVector.y / speedVector * speed);
//}
