#include "pch.h"
#include "HeadGunnerRocket.h"


HeadGunnerRocket::HeadGunnerRocket() : Entity(EntityId::GunnerRocket_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"head_gunner_rocket", 25, 9);
	sprite = new AnimatedSprite(10, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner_rocket",
		0, 1, 2, 25, 9);
}


HeadGunnerRocket::~HeadGunnerRocket()
{
	/*if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}*/

	Entity::~Entity();
}

void HeadGunnerRocket::Initialize(bool isLeft)
{
	this->SetSprite(sprite);
	this->isLeft = isLeft;
	if (isLeft) {
		this->SetVelocity(-300.0, 0.0);
		this->SetReverse(false);
	}
	else {
		this->SetVelocity(+300.0, 0.0);
		this->SetReverse(true);
	}
}

void HeadGunnerRocket::Update()
{
	if (isLeft) {
		this->AddVelocityX(-10.0);
	}
	else {
		this->AddVelocityX(+10.0);
	}

	Entity::Update();
}



void HeadGunnerRocket::OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID || impactor->GetEntityId() == EntityId::Megaman_ID)
	{
		EntityManager::GetInstance()->RemoveEntity(this);
	}
	if (impactor->GetEntityId() == EntityId::MegamanBullet_ID)
	{
		switch (side)
		{

		case Entity::Left: case Entity::TopLeft: case Entity::BottomLeft:
		{
			EntityManager::GetInstance()->RemoveEntity(this);
			break;
		}

		case Entity::Right: case Entity::TopRight: case Entity::BottomRight:
		{
			EntityManager::GetInstance()->RemoveEntity(this);
			break;
		}

		case Entity::Top:
		{
			EntityManager::GetInstance()->RemoveEntity(this);

			break;
		}

		case Entity::Bottom:
		{
			EntityManager::GetInstance()->RemoveEntity(this);
			break;
		}
		}
	}
}
