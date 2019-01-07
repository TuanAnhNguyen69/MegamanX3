#include "pch.h"
#include "ShurikenFlip.h"


ShurikenFlip::ShurikenFlip(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(40, 4, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "shuriken",
		10, 26, 10, 50, 50);
}


ShurikenFlip::~ShurikenFlip()
{
	if (handler->GetCurrentStateName() != ShurikenStateHandler::StateName::Flip) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ShurikenFlip::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	//handler->SetPreAction(ShurikenStateHandler::StateName::Flip);
	timeStartState = clock();
}

void ShurikenFlip::Update()
{
	timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;
	if (dt > 2)
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Jump);
	}
}

void ShurikenFlip::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
