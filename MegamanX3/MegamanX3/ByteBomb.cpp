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
	collDirection = CollisionDirection::None;
	isRemove = false;
	isAddWall = false;
}

void ByteBomb::Update()
{
	/*if (collDirection == CollisionDirection::CollLeft)
	{
		this->sprite->SetFrameRange(7, 8);
		Entity::Update();
		return;
	}
	if (collDirection == CollisionDirection::CollRight)
	{
		this->sprite->SetFrameRange(9, 10);
		Entity::Update();
		return;
	}*/
	if(collDirection == CollisionDirection::None)
	{
		sprite->SetFrameRange(0, 6);
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
	Entity::Update();
	if (isRemove)
	{
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
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
			isAddWall = true;
			this->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 10, 0);
			this->SetVelocity(0, 0);
			this->sprite->SetFrameRange(7, 8);
			collDirection = CollisionDirection::CollLeft;
			break;
		}

		case Entity::Right:
		{
			isAddWall = true;
			this->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + 10), 0);
			this->SetVelocity(0, 0);
			this->sprite->SetFrameRange(9, 10);
			collDirection = CollisionDirection::CollRight;
			break;
		}
		}
	}
	/*if (impactor->GetEntityId() == EntityId::Byte_ID && isAddWall)
	{
		isRemove = true;
	}*/
}
