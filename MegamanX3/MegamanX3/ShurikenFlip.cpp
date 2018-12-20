#include "pch.h"
#include "ShurikenFlip.h"


ShurikenFlip::ShurikenFlip(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(20, 2, true);
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
	handler->SetPreAction(ShurikenStateHandler::StateName::Flip);
	startState = clock();
}

void ShurikenFlip::Update()
{
	clock_t cout = clock();
	int dt = (cout - startState) / 40;
	if ((dt > 2) && (dt % 2 == 0))
	{
		handler->ChangeState(ShurikenStateHandler::StateName::Jump);
	}
}

void ShurikenFlip::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
