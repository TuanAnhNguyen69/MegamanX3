#include "pch.h"
#include "ShurikenTurn.h"


ShurikenTurn::ShurikenTurn(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(40, 4, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "shuriken",
		0, 9, 10, 50, 50);
}


ShurikenTurn::~ShurikenTurn()
{
	if (handler->GetCurrentStateName() != ShurikenStateHandler::StateName::Turn) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ShurikenTurn::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	timeStartState = clock();
	timeCreated = clock();
}

void ShurikenTurn::Update()
{
	if (!handler->GetSeen())
	{
		timeSeen = clock();
		float dt = (timeSeen - timeCreated) / 1000;
		if (dt > 7)
		{
			handler->Seen();
		}
		return;
	}

	if (handler->GetPreAction() == ShurikenStateHandler::StateName::Jump)
	{
		timeCount = clock();
		int dt = (timeCount - timeStartState) / 1000;
		if (dt > 3)
		{
			handler->ChangeState(ShurikenStateHandler::StateName::Attack1);
		}
	}
	else if (handler->GetPreAction() == ShurikenStateHandler::StateName::Attack1)
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Attack2);
	}
	else if (handler->GetPreAction() == ShurikenStateHandler::StateName::Attack2)
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Move);
	}
	else if (handler->GetPreAction() == ShurikenStateHandler::StateName::Move)
	{
		timeCount = clock();
		int dt = (timeCount - timeStartState) / 1000;
		if (dt > 2)
		{
			handler->ChangeState(ShurikenStateHandler::StateName::Flip);
		}
	}

}

void ShurikenTurn::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	/*if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{
		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top) - 10);
		}
		}
	}*/
}
