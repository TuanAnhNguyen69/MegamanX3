#include "pch.h"
#include "ShurikenDie.h"


ShurikenDie::ShurikenDie(ShurikenStateHandler *handler, Entity *entity) : ShurikenState(handler, entity)
{
	sprite = new AnimatedSprite(40, 4, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "shuriken",
		0, 0, 1, 50, 50);
}


ShurikenDie::~ShurikenDie()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void ShurikenDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	timeStartState = clock();
}

void ShurikenDie::Update()
{
	entity->AddVelocityY(15.0f);

	timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;
	if (dt > 4)
		EntityManager::GetInstance()->RemoveEntity(entity);
}

void ShurikenDie::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
