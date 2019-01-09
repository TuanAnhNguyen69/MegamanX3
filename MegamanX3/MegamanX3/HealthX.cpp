#include "pch.h"
#include "HealthX.h"


HealthBar::HealthBar(EntityId id) : Entity(id)
{
	sprite = new AnimatedSprite(10, 1, false);
	this->id = id;
	switch (id)
	{
	case EntityId::HealthX_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "x_health", 14, 52);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x_health",
			0, 16, 17, 14, 52);
		break;
	}

	case EntityId::HealthBoss_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "x_health", 14, 52);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "boss_health",
			0, 24, 25, 14, 52);
		break;
	}
	}
	

	this->SetSprite(sprite);

	this->SetScale(2, 2);
}


HealthBar::~HealthBar()
{

}

void HealthBar::Update(int value, D3DXVECTOR3 pos)
{
	
	if (id == EntityId::HealthX_ID)
	{
		this->SetPosition(pos.x - SCREEN_WIDTH / 2 + 24, pos.y - SCREEN_HEIGHT / 2 + 120);
		this->sprite->SetFrameRange(value, value);
	}
	else if (id == EntityId::HealthBoss_ID)
	{
		this->SetPosition(pos.x + SCREEN_WIDTH / 2 - 24, pos.y - SCREEN_HEIGHT / 2 + 120);
		this->sprite->SetFrameRange(value / 2, value / 2);
	}
	Entity::Update();
}

void HealthBar::Initialize()
{
	
}


