#include "pch.h"
#include "Box.h"


Box::Box(EntityId id) : Entity(id)
{
	this->id = id;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box", 50, 50);
	sprite = new AnimatedSprite(30, 1, true);
	switch (id)
	{
	case Box_ID:
	{
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 50);
		this->SetBound(50, 50);
	}
	break;

	case DoubleBox_ID:
	{
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 100, 50);
		this->SetBound(100, 50);
	}
	break;
	case TrippleBox_ID:
	{
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 150);
		this->SetBound(50, 150);
	}
	break;

	case QuadraBox_ID:
	{
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 200);
		this->SetBound(50, 200);
	}
	break;

	case VerticalBombBox_ID:
	{
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 50);
	}
	break;

	case HorizontalBombBox_ID:
	{
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 50);
	}
	break;

	default:
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 50);
	}
}


Box::~Box()
{

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
	if (impactor->GetEntityId() == EntityId::Platform_ID && this->id == EntityId::Box_ID)
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

int Box::GetHP()
{
	return this->HP;
}

void Box::SubHP(int damage)
{
	HP -= damage;
}
