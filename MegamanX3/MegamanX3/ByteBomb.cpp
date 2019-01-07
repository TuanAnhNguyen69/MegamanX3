#include "pch.h"
#include "ByteBomb.h"


ByteBomb::ByteBomb() : Entity(EntityId::ByteBomb_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"byte_bomb", 22, 22);
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte_bomb",
		0, 10, 11, 22, 22);
}


ByteBomb::~ByteBomb()
{
}

void ByteBomb::Initailize(MoveDirection moveDirection)
{
	this->hitted = false;
	this->moveDirection = moveDirection;
	this->SetSprite(sprite);
	collDirection = CollisionDirection::None;
	isRemove = false;
	isAddWall = false;
}

void ByteBomb::Update()
{
	if (this->hitted) {
		if (sprite->IsFinished()) {
			EntityManager::GetInstance()->RemoveEntity(this);
			return;
		}
	}
	else {
		if (isRemove)
		{
			EntityManager::GetInstance()->RemoveEntity(this);
			return;
		}

		if (collDirection == CollisionDirection::None)
		{
			sprite->SetFrameRange(0, 6);
			if (moveDirection == MoveDirection::Left)
			{
				this->SetVelocityX(-Define::BYTEBOMB_SPEED);
			}
			else if (moveDirection == MoveDirection::Right)
			{
				this->SetVelocityX(Define::BYTEBOMB_SPEED);
			}
		}
	}
	
	Entity::Update();
	
}

void ByteBomb::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (!this->hitted) {
		if (impactor->GetEntityId() == EntityId::Platform_ID)
		{
			switch (side)
			{
			case Entity::Left:
			{
				this->SetBound(1, 30);
				isAddWall = true;
				this->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->SetVelocity(0, 0);
				this->sprite->SetFrame(7);
				collDirection = CollisionDirection::CollLeft;
				break;
			}

			case Entity::Right:
			{
				this->SetBound(1, 30);
				isAddWall = true;
				this->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left) - 5, 0);
				this->SetVelocity(0, 0);
				this->sprite->SetFrame(9);
				collDirection = CollisionDirection::CollRight;
				break;
			}
			}
		}
		if (impactor->GetEntityId() == EntityId::Byte_ID && isAddWall)
		{
			this->SetVelocity(0, 0);
			sprite = new AnimatedSprite(15, 1, false);
			sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
				0, 7, 8, 50, 50);
			this->SetSprite(sprite);
			this->hitted = true;
			isRemove = true;
		}
	}
	
}

bool ByteBomb::IsHitted()
{
	return this->hitted;
}
