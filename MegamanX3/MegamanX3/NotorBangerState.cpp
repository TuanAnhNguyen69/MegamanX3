#include "pch.h"
#include "NotorBangerState.h"


/*******************State***************************************/
NotorBangerState::NotorBangerState(NotorBangerStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = entity;
}

NotorBangerState::~NotorBangerState()
{
}

void NotorBangerState::Load()
{
}

void NotorBangerState::Update()
{
}

void NotorBangerState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

/*******************Standing***************************************/
NotorBangerStanding::NotorBangerStanding(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		7, 9, 10, 50, 50);
}
NotorBangerStanding::~NotorBangerStanding()
{
}

void NotorBangerStanding::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void NotorBangerStanding::Update()
{
}

void NotorBangerStanding::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

/*******************Fire***************************************/
NotorBangerFire::NotorBangerFire(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{

}

NotorBangerFire::~NotorBangerFire()
{
}

void NotorBangerFire::Load()
{
}

void NotorBangerFire::Update()
{
}

void NotorBangerFire::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}


/*******************Jump***************************************/
NotorBangerJump::NotorBangerJump(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{

}
NotorBangerJump::~NotorBangerJump()
{
}

void NotorBangerJump::Load()
{
}

void NotorBangerJump::Update()
{
}

void NotorBangerJump::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}


/*******************Damaged***************************************/
NotorBangerDamaged::NotorBangerDamaged(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{

}
NotorBangerDamaged::~NotorBangerDamaged()
{
}

void NotorBangerDamaged::Load()
{
}

void NotorBangerDamaged::Update()
{
}


void NotorBangerDamaged::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}


/*******************Die***************************************/
NotorBangerDie::NotorBangerDie(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{

}
NotorBangerDie::~NotorBangerDie()
{
}

void NotorBangerDie::Load()
{
}

void NotorBangerDie::Update()
{
}

void NotorBangerDie::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}


