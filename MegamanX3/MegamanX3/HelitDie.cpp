#include "pch.h"
#include "HelitDie.h"


HelitDie::HelitDie(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
		0, 7, 8, 50, 50);
}

HelitDie::~HelitDie()
{

	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
	
}

void HelitDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	
}

void HelitDie::Update()
{
	if (handler->GetHP() == 0) {
		if (sprite->IsFinished()) {
			/*entity->SetSprite(nullptr);	
			entity->SetBound(0, 0);
			handler->Died();
			delete entity;*/
			EntityManager::GetInstance()->RemoveEntity(entity);
		}
	}
}

void HelitDie::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
