#include "pch.h"
#include "Explosive.h"


Explosive::Explosive()
{
	sprite = new AnimatedSprite(15, 1, false);
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "die", 50, 50);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
		0, 7, 8, 50, 50);
	this->SetSprite(sprite);
	this->SetScale(4, 4);
}


Explosive::~Explosive()
{
}

void Explosive::Update()
{
	if (sprite->IsFinished())
	{
		EntityManager::GetInstance()->RemoveEntity(this);
		return;
	}
	Entity::Update();
}
