#include "pch.h"
#include "CargoSole.h"


CargoSole::CargoSole() : Entity(EntityId::CargoSole_ID)
{
	sprite = new AnimatedSprite(10, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "cargo_sole",
		0, 0, 1, 144, 88);
	remove = false;
}


CargoSole::~CargoSole()
{
}

void CargoSole::Initialize()
{
	alight = false;
	this->SetSprite(sprite);
	this->SetVelocity(0, 0);
}

void CargoSole::Update()
{
	if (remove)
	{
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}
	Entity::Update();
	if (alight)
	{
		this->SetVelocity(0, 0);
	}
}

void CargoSole::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{
		case Entity::Bottom:
		case Entity::BottomLeft:
		case Entity::BottomRight:
			this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->SetVelocity(0,0);
			this->alight = true;
			break;
		}
	}
}

//RECT CargoSole::GetBound()
//{
//	RECT bound;
//	bound.left = this->GetPosition().x - width / 2;
//	bound.right = bound.left + width;
//	bound.top = this->GetPosition().y - height / 2 + 72;
//	bound.bottom = bound.top + height;
//	return bound;
//}

bool CargoSole::HadAlight()
{
	return this->alight;
}

void CargoSole::SetRemove()
{
	remove = true;
}
