#include "pch.h"
#include "BlastHornetDie.h"


BlastHornetDie::BlastHornetDie(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet_die",
		0, 0, 1, 100, 100);
}


BlastHornetDie::~BlastHornetDie()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Die) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	timeStartState = clock();
	entity->SetBound(30, 100);

	Sound::getInstance()->loadSound((char*)"sound/explosion.wav", "explosion_die");
	Sound::getInstance()->play("explosion_die", true, 0);
}

void BlastHornetDie::Update()
{
	entity->AddVelocityY(15);

	timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;
	if (dt > 5)
		entity->SetRemove();
}

void BlastHornetDie::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{
		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			entity->SetVelocity(0, 0);
			break;
		}
		}
	}
}
