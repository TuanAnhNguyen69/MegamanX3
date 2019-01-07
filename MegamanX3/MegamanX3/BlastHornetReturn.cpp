#include "pch.h"
#include "BlastHornetReturn.h"


BlastHornetReturn::BlastHornetReturn(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(30, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		0, 2, 6, 100, 100);
}


BlastHornetReturn::~BlastHornetReturn()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Return) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetReturn::Load()
{
	entity->SetVelocity(0, 0);
	entity->SetSprite(sprite);
	curPos = D3DXVECTOR3(entity->GetPosition().x, entity->GetPosition().y, 0);
	//isGoToPointA = false;
	route = Route::Unknow;

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

void BlastHornetReturn::Update()
{
	BlastHornetState::Update();

	/*if ((entity->GetPosition().x == handler->GetPointA().x && entity->GetPosition().y == handler->GetPointA().y) ||
		(entity->GetPosition().x == handler->GetPointB().x && entity->GetPosition().y == handler->GetPointB().y))
	{
		isChangePos = true;
	}
	else
	{
		isChangePos = false;
	}*/

	/*if (entity->GetPosition().x == handler->GetPointA().x && entity->GetPosition().y == handler->GetPointA().y)
	{
		route = Route::AtA;
	}
	else if (entity->GetPosition().x == handler->GetPointB().x && entity->GetPosition().y == handler->GetPointB().y)
	{
		route = Route::AtB;
	}
	else
	{
		route = Route::Moving;
	}*/


	//Nếu BlastHornet trở về A
	if (isGoToPointA)
	{
		//Nếu đã ở A thì chuyển sang State Prepare
		if (entity->GetPosition().x == handler->GetPointA().x && entity->GetPosition().y == handler->GetPointA().y)
		{
			entity->SetReverse(false);
			handler->ChangeState(BlastHornetStateHandler::StateName::Prepare);
		}
		//Nếu chưa ở A
		else
		{
			if(route == Route::AtA || route)
			//if (isChangePos)
				GoTo(curPos, handler->GetPointA(), 10);
		}
	}
	//Nếu BlastHornet trở về B
	else
	{
		//Nếu đã ở B thì chuyển sang State Prepare
		if (entity->GetPosition().x == handler->GetPointB().x && entity->GetPosition().y == handler->GetPointB().y)
		{
			entity->SetReverse(true);
			handler->ChangeState(BlastHornetStateHandler::StateName::Prepare);
		}
		//Nếu chưa ở B
		else
		{
			//if(isChangePos)
				GoTo(curPos, handler->GetPointB(), 10);
		}
	}

	if (handler->GetHP() <= Define::BLASTHORNET_HP / 2)
	{
		handler->ChangeState(BlastHornetStateHandler::StateName::Fly);
	}
}

void BlastHornetReturn::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
