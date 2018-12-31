#include "pch.h"
#include "BlastHornetFly.h"


BlastHornetFly::BlastHornetFly(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(30, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		0, 2, 6, 100, 100);
}


BlastHornetFly::~BlastHornetFly()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Fly) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetFly::Load()
{
	entity->SetSprite(sprite);
}

void BlastHornetFly::Update()
{
}

void BlastHornetFly::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
