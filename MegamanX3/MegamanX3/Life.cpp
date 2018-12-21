#include "pch.h"
#include "Life.h"


Life::Life()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"life", 16, 12);
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "life",
		0, 3, 4, 16, 12);
}


Life::~Life()
{
}

void Life::Initialize()
{
	this->SetSprite(sprite);
}

void Life::Update()
{
	Entity::Update();
}

void Life::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
