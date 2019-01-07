#include "pch.h"
#include "Box.h"


Box::Box(EntityId id) : Entity(id)
{
	this->isFall = false;
	this->id = id;
	sprite = new AnimatedSprite(30, 1, true);
	switch (id)
	{
	case Box_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box", 72, 72);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 72, 72);
		this->SetBound(72, 72);
	}
	break;

	case DoubleBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box2", 144, 72);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box3",
			0, 0, 1, 144, 72);
		this->SetBound(144, 72);
	}
	break;
	case TrippleBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box3", 72, 216);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box3",
			0, 0, 1, 72, 216);
		this->SetBound(72, 216);
	}
	break;

	case QuadraBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box4", 72, 288);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box4",
			0, 0, 1, 72, 288);
		this->SetBound(72, 288);
	}
	break;

	case VerticalBombBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_vetical", 118, 144);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_vetical",
			0, 0, 1, 118, 144);
		this->SetBound(118, 144);

	}
	break;

	case HorizontalBombBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_vetical", 144, 96);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_horizontal",
			0, 0, 1, 144, 96);
		this->SetBound(144, 96);
	}
	break;

	default:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box", 72, 72);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 50);
		this->SetBound(50, 50);
	}
	break;
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

	if (HP <= 0)
	{
		//Nổ
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

	if (impactor->GetEntityId() == EntityId::MegamanBullet_ID)
	{
		//Nhận damage
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
