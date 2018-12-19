#include "pch.h"
#include "NotorBangerShoot.h"


NotorBangerShoot::NotorBangerShoot(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		4, 5, 2, 50, 50);
}

NotorBangerShoot::~NotorBangerShoot()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Shoot) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerShoot::Load()
{
	entity->SetSprite(sprite);
}

void NotorBangerShoot::Update()
{
	for (int count = 0; count < 3; count++)
	{
		sprite->SetFrameRange(4, 5);
		//new NotorBangerCanon(entity->GetPosition(), entity.HP);
		if (sprite->IsFinished())
		{
			sprite->ResetFrame();
		}
	}
}

void NotorBangerShoot::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
