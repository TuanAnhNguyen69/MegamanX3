#include "pch.h"
#include "Box.h"


Box::Box() : Entity(EntityId::Box_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"box", 50, 50);
	sprite = new AnimatedSprite(30, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
		0, 0, 1, 50, 50);
}


Box::~Box()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void Box::Update()
{
	Entity::Update();
	if (this->isFall)
	{
		this->SetVelocityY(Define::BOX_SPEED);
	}
}

void Box::Initialize(bool isFall)
{
	this->isFall = isFall;
	this->SetVelocity(0, 0);
	isCollPlatform = false;
}

void Box::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{
		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
			this->SetVelocity(0, 0);
			this->isFall = false;
			this->isCollPlatform = true;
			break;
		}
		}
	}
}

void Box::SetFall(bool isFall)
{
	this->isFall = isFall;
}

bool Box::IsFall()
{
	return this->isFall;
}

bool Box::IsCollisionPlatform()
{
	return this->isCollPlatform;
}
