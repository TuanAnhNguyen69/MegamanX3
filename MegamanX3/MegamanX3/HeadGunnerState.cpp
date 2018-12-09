#include "pch.h"
#include "HeadGunnerState.h"


/*******************State***************************************/
HeadGunnerState::HeadGunnerState(HeadGunnerStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = entity;
}

HeadGunnerState::~HeadGunnerState()
{
	
}

void HeadGunnerState::Load()
{
}

void HeadGunnerState::Update()
{
}

void HeadGunnerState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

/*******************Standing***************************************/
HeadGunnerStanding::HeadGunnerStanding(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 1, 2, 50, 50);
}
HeadGunnerStanding::~HeadGunnerStanding()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerStanding::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HeadGunnerStanding::Update()
{
}

void HeadGunnerStanding::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

/*******************Fire***************************************/
HeadGunnerFire::HeadGunnerFire(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 7, 2, 50, 50);
}

HeadGunnerFire::~HeadGunnerFire()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerFire::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HeadGunnerFire::Update()
{
}

void HeadGunnerFire::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}


/*******************Damaged***************************************/
HeadGunnerDamaged::HeadGunnerDamaged(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 1, 2, 50, 50);
}
HeadGunnerDamaged::~HeadGunnerDamaged()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerDamaged::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HeadGunnerDamaged::Update()
{
}


void HeadGunnerDamaged::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}


/*******************Die***************************************/
HeadGunnerDie::HeadGunnerDie(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{

}
HeadGunnerDie::~HeadGunnerDie()
{

}

void HeadGunnerDie::Load()
{

}

void HeadGunnerDie::Update()
{

}

void HeadGunnerDie::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}


