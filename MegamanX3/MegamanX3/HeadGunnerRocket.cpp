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
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
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
		switch (side)
		{
		case Entity::Left: case Entity::TopLeft: case Entity::BottomLeft:
		{
			/*this->AddPosition(data.RegionCollision.right - data.RegionCollision.left + 1, 0);
			this->SetVelocity(0, 0);*/
			EntityManager::GetInstance()->RemoveEntity(this);
			break;
		}

		case Entity::Right: case Entity::TopRight: case Entity::BottomRight:
		{
			/*this->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + 1), 0);
			this->SetVelocity(0, 0);*/
			EntityManager::GetInstance()->RemoveEntity(this);
			break;
		}

		case Entity::Top:
		{
			/*this->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top + 1);
			this->SetVelocity(0, 0);*/
			EntityManager::GetInstance()->RemoveEntity(this);
			break;
		}

		case Entity::Bottom:
		{

			/*this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
			this->SetVelocity(0, 0);*/
			/*this->AddVelocityY(-10.0f);*/
			EntityManager::GetInstance()->RemoveEntity(this);
			break;
		}
		}
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
