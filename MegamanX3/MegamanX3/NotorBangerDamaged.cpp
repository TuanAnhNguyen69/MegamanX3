#include "pch.h"
#include "NotorBangerDamaged.h"


NotorBangerDamaged::NotorBangerDamaged(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		0, 8, 10, 50, 50);
}
NotorBangerDamaged::~NotorBangerDamaged()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Damaged) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerDamaged::Load()
{
	entity->SetSprite(sprite);
	sprite->ResetFrame();
}

void NotorBangerDamaged::Update()
{
	if (sprite->IsFinished()) {
		handler->ChangeState(NotorBangerStateHandler::StateName::Standing);
	}
}

void NotorBangerDamaged::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}