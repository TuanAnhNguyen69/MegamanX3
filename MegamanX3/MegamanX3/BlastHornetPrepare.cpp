#include "pch.h"
#include "BlastHornetPrepare.h"


BlastHornetPrepare::BlastHornetPrepare(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(30, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		0, 2, 6, 100, 100);
}


BlastHornetPrepare::~BlastHornetPrepare()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Prepare) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetPrepare::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void BlastHornetPrepare::Update()
{
	BlastHornetState::Update();
	//if (HP > 20) nếu máu còn nhiều hơn 1/2
	{
		if (handler->GetPreAction() == BlastHornetStateHandler::StateName::Drop)
		{
			handler->ChangeState(BlastHornetStateHandler::StateName::Prick);
		}
		else
		{
			handler->ChangeState(BlastHornetStateHandler::StateName::Drop);
		}
	}
	//else
	{
		handler->ChangeState(BlastHornetStateHandler::StateName::Fly);
	}
}

void BlastHornetPrepare::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
