#include "pch.h"
#include "ByteBomb.h"


ByteBomb::ByteBomb() : Entity(EntityId::ByteBomb_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"byte_bomb", 22, 22);
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "byte_bomb",
		0, 6, 9, 22, 22);
}


ByteBomb::~ByteBomb()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void ByteBomb::Initailize(MoveDirection moveDirection)
{
	this->moveDirection = moveDirection;
	this->SetSprite(sprite);
}

void ByteBomb::Update()
{
	Entity::Update();
	//sprite->SetFrameRange(0, 6);
	if (moveDirection == MoveDirection::Left)
	{
		this->SetVelocityX(-Define::BYTEBOMB_SPEED);
		//this->AddVelocityX(-Define::BYTEBOMB_ACCELERATION);
	}
	else if (moveDirection == MoveDirection::Right)
	{
		this->SetVelocityX(Define::BYTEBOMB_SPEED);
		//this->AddVelocityX(Define::BYTEBOMB_ACCELERATION);
	}
}

void ByteBomb::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{
		case Entity::Left:
		{
			this->sprite->SetFrameRange(7, 7);
			this->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->SetVelocityX(0);
			break;
		}

		case Entity::Right:
		{
			this->sprite->SetFrameRange(8, 8);
			this->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->SetVelocityX(0);
			break;
		}
		}
	}
}
