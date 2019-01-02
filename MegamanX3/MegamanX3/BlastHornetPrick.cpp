#include "pch.h"
#include "BlastHornetPrick.h"


BlastHornetPrick::BlastHornetPrick(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		6, 23, 6, 100, 100);
}


BlastHornetPrick::~BlastHornetPrick()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Prepare) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetPrick::Load()
{
	isStopState = false;
	entity->SetVelocity(0, 0);
	entity->SetSprite(sprite);
	handler->SetPreAction(BlastHornetStateHandler::StateName::Prick);
	targetPos = handler->GetPlayerPos();
	timeStartState = clock();
}

void BlastHornetPrick::Update()
{
	BlastHornetState::Update();

	//Nếu đang ở A
	if (entity->GetPosition().x == handler->GetPointA().x && entity->GetPosition().y == handler->GetPointA().y)
	{
		curPos = handler->GetPointA();
		//GoOn(handler->GetPointA(), targetPos, 50);
	}
	//Nếu đang ở B
	else if (entity->GetPosition().x == handler->GetPointB().x && entity->GetPosition().y == handler->GetPointB().y)
	{
		curPos = handler->GetPointB();
		//GoOn(handler->GetPointB(), targetPos, 50);
	}

	if (sprite->IsFinished())
	{
		GoOn(curPos, targetPos, 50);
	}
	
	if (isStopState)
	{
		timeCount = clock();
		int dt = (timeCount - timeStartState) / 1200;
		if(dt > 3)
		{
			sprite->ResetFrame();
			handler->ChangeState(BlastHornetStateHandler::StateName::Return);
		}		
	}
}

void BlastHornetPrick::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{

			case Entity::Left:
			{
				entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				entity->SetVelocity(0, 0);
				isStopState = true;
				break;
			}

			case Entity::Right:
			{
				entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				entity->SetVelocity(0, 0);
				isStopState = true;
				break;
			}

			case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
			{
				entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
				entity->SetVelocity(0, 0);
				isStopState = true;
				break;
			}

			case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
			{
				entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				entity->SetVelocity(0, 0);
				isStopState = true;
				break;
			}
		}
	}
}
