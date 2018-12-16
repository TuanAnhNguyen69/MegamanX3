#include "pch.h"
#include "NotorBangerState.h"
#include "NotorBanger.h"


#pragma region NortoBangerState
/*******************State***************************************/
NotorBangerState::NotorBangerState(NotorBangerStateHandler *handler, Entity *entity)
{
	this->handler = handler;
	this->entity = (NotorBanger*)entity;
}
#
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
#pragma endregion


#pragma region NotorBangerStanding
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
#pragma endregion


#pragma region NotorBangerFire
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
#pragma endregion


#pragma region NotorBangerJump
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
	entity->SetVelocityY(Define::NOTORBANGER_MIN_JUMP_VELOCITY);
	acceleratorX = 14.0f;
	acceleratorY = 15.0f;
	sprite->ResetFrame();
}

void NotorBangerJump::Update()
{
	entity->AddVelocityY(acceleratorY);

	if (entity->GetVelocity().y >= 0) {
		entity->AddVelocityY(acceleratorY);
		if (entity->GetVelocity().y > Define::NOTORBANGER_MAX_JUMP_VELOCITY) {
			entity->SetVelocityY(Define::NOTORBANGER_MAX_JUMP_VELOCITY);
		}

		//Truyền vị trí Megaman để NotorBanger nhảy về hướng đó
		//Nếu bên trái
		if (true)
		{
			entity->SetReverse(false);
			if (entity->GetVelocity().x > -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
				entity->AddVelocityX(-acceleratorX);
				if (entity->GetVelocity().x < -Define::NOTORBANGER_MAX_RUNNING_SPEED) {
					entity->SetVelocityX(-Define::NOTORBANGER_MAX_RUNNING_SPEED);
				}
			}
		}
		//Nếu bên phải
		else
		{
			entity->SetReverse(true);
			if (entity->GetVelocity().x < Define::NOTORBANGER_MAX_RUNNING_SPEED) {
				entity->AddVelocityX(acceleratorX);
				if (entity->GetVelocity().x >= Define::NOTORBANGER_MAX_RUNNING_SPEED) {
					entity->SetVelocityX(Define::NOTORBANGER_MAX_RUNNING_SPEED);
				}
			}
		}
		
	}

	if (handler->GetMoveDirection() == NotorBangerStateHandler::MoveDirection::MoveToLeft) {
		if (entity->GetVelocity().x < 0) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x > 0) {
				entity->SetVelocityX(0);
			}
		}
	}
	else if (handler->GetMoveDirection() == NotorBangerStateHandler::MoveDirection::MoveToRight) {
		if (entity->GetVelocity().x > 0) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < 0) {
				entity->SetVelocityX(0);
			}
		}
	}

	//Vd
	sprite->SetFrameRange(3, 5);

}

void NotorBangerJump::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{
		entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
		entity->SetVelocityX(0);
		break;
	}

	case Entity::Right:
	{
		entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
		entity->SetVelocityX(0);
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
		entity->SetVelocityY(0);
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		entity->SetVelocityY(0);
	}


	default:
		break;
	}
}
#pragma endregion


#pragma region NotorBangerDamaged
/*******************Damaged***************************************/
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

void NotorBangerDamaged::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
#pragma endregion

//Chưa xử lý
#pragma region NotorBangerDie
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

#pragma endregion

//Gộp chung jump và falling lại thành jump, nên ko xử lý fall
#pragma region NotorBangerFalling
/*******************Falling***************************************/
NotorBangerFalling::NotorBangerFalling(NotorBangerStateHandler *handler, Entity *entity) : NotorBangerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "notor_banger",
		0, 8, 10, 50, 50);
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
	entity->SetSprite(sprite);
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;
	sprite->ResetFrame();
}

void NotorBangerFalling::Update()
{
	/*entity->AddVelocityY(acceleratorY);
	if (entity->GetVelocity().y > Define::NOTORBANGER_MAX_JUMP_VELOCITY) {
		entity->SetVelocityY(Define::NOTORBANGER_MAX_JUMP_VELOCITY);
	}*/
}

void NotorBangerFalling::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
#pragma endregion


