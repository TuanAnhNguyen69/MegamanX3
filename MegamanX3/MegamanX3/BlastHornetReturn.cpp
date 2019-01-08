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

	if (handler->GetPreAction() == BlastHornetStateHandler::StateName::Drop)
	{
		//Nếu player ở gần B hơn A sẽ đi về B
		if (abs(handler->GetPlayerPos().x - handler->GetPointA().x) > abs(handler->GetPlayerPos().x - handler->GetPointB().x))
		{
			isGoToPointA = false;
		}
		//Nếu player ở gần A hơn B sẽ đi về A
		else
		{
			isGoToPointA = true;
		}
	}
	else if (handler->GetPreAction() == BlastHornetStateHandler::StateName::Prick)
	{
		//Nếu player ở gần B hơn A sẽ đi về A
		if (abs(handler->GetPlayerPos().x - handler->GetPointA().x) > abs(handler->GetPlayerPos().x - handler->GetPointB().x))
		{
			isGoToPointA = true;
		}
		//Nếu player ở gần A hơn B sẽ đi về B
		else
		{
			isGoToPointA = false;
		}
	}
	
}

void BlastHornetReturn::Update()
{
	BlastHornetState::Update();

	if (!handler->GetSeen())
	{
		timeSeen = clock();
		float dt = (timeSeen - timeCreated) / 1000;
		if (dt > 8)
		{
			handler->Seen();
		}
		return;
	}

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
				entity->GoTo(curPos, handler->GetPointA(), 10);
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
			entity->GoTo(curPos, handler->GetPointB(), 10);
		}
	}
}

void BlastHornetReturn::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
