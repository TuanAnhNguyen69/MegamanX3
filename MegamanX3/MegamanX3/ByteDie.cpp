#include "pch.h"
#include "ByteDie.h"


ByteDie::ByteDie(ByteStateHandler *handler, Entity *entity) : ByteState(handler, entity)
{
	sprite = new AnimatedSprite(10, 0.5, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte",
		0, 1, 4, 100, 100);
}


ByteDie::~ByteDie()
{
	if (handler->GetCurrentStateName() != ByteStateHandler::StateName::Die)
	{
		if (sprite)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
}

void ByteDie::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	timeStartState = clock();
}

void ByteDie::Update()
{
	timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;
	if (dt > 4)
		entity->SetRemove();
}

void ByteDie::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
