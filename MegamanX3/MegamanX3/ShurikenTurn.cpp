#include "pch.h"
#include "ShurikenTurn.h"


ShurikenTurn::ShurikenTurn(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(20, 2, true);
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
	startState = clock();
}

void ShurikenTurn::Update()
{
	//switch (handler->GetPreAction())
	//{
	//case ShurikenStateHandler::StateName::Jump:
	//	clock_t cout = clock();
	//	int dt = (cout - startState) / 40;
	//	if ((dt > 2) && (dt % 2 == 0))
	//	{
	//		handler->ChangeState(ShurikenStateHandler::StateName::Attack1);
	//	}
	//	break;
	//case ShurikenStateHandler::StateName::Attack1:
	//	handler->ChangeState(ShurikenStateHandler::StateName::Attack2);
	//	break;
	//case ShurikenStateHandler::StateName::Attack2:
	//	handler->ChangeState(ShurikenStateHandler::StateName::Move);
	//	break;
	///*case ShurikenStateHandler::StateName::Move:
	//	handler->ChangeState(ShurikenStateHandler::StateName::Flip);
	//	break;*/
	//}
	entity->AddVelocityY(Define::SHURIKEN_ACCELERATION_FALL_Y);

	if (handler->GetPreAction() == ShurikenStateHandler::StateName::Jump)
	{
		clock_t cout = clock();
		int dt = (cout - startState) / 40;
		if ((dt > 3) && (dt % 3 == 0))
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

}

void ShurikenTurn::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{
		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		}
		}
	}
}
