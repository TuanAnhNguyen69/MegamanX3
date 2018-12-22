#include "pch.h"
#include "Canon.h"



Canon::Canon() : Entity(EntityId::Canon_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"canon", 9, 9);
	sprite = new AnimatedSprite(10, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "canon",
		0, 0, 1, 9, 9);
}


Canon::~Canon()
{
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}

void Canon::Initialize(bool isHigh, bool isLeft)
{
	this->isHigh = isHigh;
	this->isLeft = isLeft;
	if (!isHigh)
	{
		if (isLeft)
		{
			this->SetVelocityX(-300.0f);
			this->SetVelocityY(-400.0f);
		}
		else
		{
			this->SetVelocityX(300.0f);
			this->SetVelocityY(-400.0f);
		}
	}
	else
	{
		if (isLeft)
		{

		}
		else
		{

		}
	}
}

void Canon::Update()
{
	if (!isHigh)
	{
		this->AddVelocityY(10.0f);
		if (this->GetVelocity().y > 0)
		{
			this->AddVelocityY(10.0f);
		}

		if (isLeft)
		{
			this->AddVelocityX(-20.0f);
			if (this->GetVelocity().x < 0)
			{
				this->AddVelocityX(15.0f);
			}
		}
		else
		{
			this->AddVelocityX(20.0f);
			if (this->GetVelocity().x < 0)
			{
				this->AddVelocityX(-15.0f);
			}
		}
	}

	//this->AddVelocityY(-10.0f);
	Entity::Update();
	//float dt = Timer::GetDeltaTime();

	//this->SetPosition(this->GetVelocity().x * dt, this->GetPosition().y);

	//float dx = x0 - this->GetPosition().x;

	//float relaHeight = 0.03f;			//chiều cao tương dối: càng lớn thấp (rớt nhanh hơn)
	//float relaDistance = 4.0f;			//chiều xa tương đối : càng lớn xa 

	//this->SetPosition(this->GetVelocity().x, -relaHeight*(dx*dx) + relaDistance*dx + y0);
}



void Canon::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID || impactor->GetEntityId() == EntityId::Megaman_ID)
	{
		switch (side)
		{

			case Entity::Left:
			{
				/*this->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->SetVelocity(0, 0);*/
				EntityManager::GetInstance()->RemoveEntity(this);
				break;
			}

			case Entity::Right:
			{
				/*this->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->SetVelocity(0, 0);*/
				EntityManager::GetInstance()->RemoveEntity(this);
				break;
			}

			case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
			{
				/*this->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
				this->SetVelocity(0, 0);*/
				EntityManager::GetInstance()->RemoveEntity(this);
				break;
			}

			case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
			{
				/*this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				this->SetVelocity(0, 0);*/
				EntityManager::GetInstance()->RemoveEntity(this);
				break;
			}
		}
	}
}
