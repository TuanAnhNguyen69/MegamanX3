#include "pch.h"
#include "NotorBangerState.h"
#include "NotorBanger.h"


/*******************State***************************************/
NotorBangerState::NotorBangerState(NotorBangerStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = (NotorBanger*)entity;
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
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		0, 0, 2, 50, 50);
}
NotorBangerStanding::~NotorBangerStanding()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerStanding::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void NotorBangerStanding::Update()
{
	if (handler->GetAction())
		handler->ChangeState(NotorBangerStateHandler::StateName::Fire);
}

void NotorBangerStanding::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

/*******************Fire***************************************/
NotorBangerFire::NotorBangerFire(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		4, 5, 2, 50, 50);
}

NotorBangerFire::~NotorBangerFire()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Fire) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerFire::Load()
{
	entity->SetSprite(sprite);
}

void NotorBangerFire::Update()
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

void NotorBangerFire::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}


/*******************Jump***************************************/
NotorBangerJump::NotorBangerJump(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		0, 3, 2, 50, 50);
}
NotorBangerJump::~NotorBangerJump()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Jump) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerJump::Load()
{
	entity->SetSprite(sprite);
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
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Damaged) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
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
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Die) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
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

/*******************Falling***************************************/
NotorBangerFalling::NotorBangerFalling(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
}

NotorBangerFalling::~NotorBangerFalling()
{
	if (handler->GetCurrentStateName() != NotorBangerStateHandler::StateName::Falling) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void NotorBangerFalling::Load()
{
}

void NotorBangerFalling::Update()
{
}

void NotorBangerFalling::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
