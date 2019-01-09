#include "pch.h"
#include "HealthX.h"


HealthBar::HealthBar() : Entity()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"x_health", 14, 52);
	sprite = new AnimatedSprite(10, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x_health",
		0, 16, 17, 14, 52);

	this->SetSprite(sprite);

	this->SetScale(2, 2);
}


HealthBar::~HealthBar()
{

}

void HealthBar::Update(int value, D3DXVECTOR3 pos)
{
	this->SetPosition(pos.x - SCREEN_WIDTH / 2  + 24, pos.y - SCREEN_HEIGHT / 2 + 120);
	this->sprite->SetFrameRange(value, value);
	Entity::Update();

}

void HealthBar::Initialize()
{
	
}

void HealthBar::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
