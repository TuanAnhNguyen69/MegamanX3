#include "pch.h"
#include "HealthX.h"


HealthX::HealthX(Player *player) : Entity(EntityId::HealthX_ID)
{
	sprite = new AnimatedSprite(10, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x_health",
		0, 16, 17, 14, 52);

	this->player = player;

	this->SetSprite(sprite);
}


HealthX::~HealthX()
{

}

void HealthX::Update()
{
	Entity::Update();
	this->SetPosition(player->GetPosition().x - 100, player->GetPosition().y - 100);
	this->sprite->SetFrame(((Enemy*)player)->GetHP() / 2);
}

void HealthX::Initialize()
{
	
}
