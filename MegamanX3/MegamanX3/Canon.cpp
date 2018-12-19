#include "pch.h"
#include "Canon.h"



Canon::Canon() : Entity (EntityId::Canon_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"canon", 9, 9);
	sprite = new AnimatedSprite(10, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "canon",
		0, 0, 1, 9, 9);
}


Canon::~Canon()
{
}

void Canon::Initialize(bool _isHigh)
{
	isHigh = _isHigh;
	//x0 = this->GetPosition().x;
	//y0 = this->GetPosition().y;
	this->SetVelocityX(-300.0f);
	this->SetVelocityY(-400.0f);
}

void Canon::Update()
{
	this->AddVelocityY(15.0f);
	if (this->GetVelocity().x < 0)
	{
		this->AddVelocityX(14);
		if (this->GetVelocity().x > 0)
		{
			this->AddVelocityX(-10.0);
		}
	}
	if (this->GetVelocity().y > 0)
	{
		this->AddVelocityY(8.0f);
	}
	this->AddVelocityX(-20.0);
	//this->AddVelocityY(-10.0f);
	Entity::Update();
	//float dt = Timer::GetDeltaTime();

	//this->SetPosition(this->GetVelocity().x * dt, this->GetPosition().y);

	//float dx = x0 - this->GetPosition().x;

	//float relaHeight = 0.03f;			//chiều cao tương dối: càng lớn thấp (rớt nhanh hơn)
	//float relaDistance = 4.0f;			//chiều xa tương đối : càng lớn xa 

	//this->SetPosition(this->GetVelocity().x, -relaHeight*(dx*dx) + relaDistance*dx + y0);
}



void Canon::OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
