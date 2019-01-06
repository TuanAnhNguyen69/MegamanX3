#include "pch.h"
#include "HelitDamaged.h"


HelitDamaged::HelitDamaged(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit",
		0, 1, 2, 50, 50);
}
HelitDamaged::~HelitDamaged()
{
	//if (handler->GetCurrentStateName() != HelitStateHandler::StateName::Damaged) 
	{
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HelitDamaged::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HelitDamaged::Update()
{
}


void HelitDamaged::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
