#include "pch.h"
#include "Thorn.h"


Thorn::Thorn() : Entity(EntityId::Thorn_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"thorn", 16, 80);
	sprite = new AnimatedSprite(1, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "thorn",
		0, 0, 1, 16, 80);
}


Thorn::~Thorn()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void Thorn::Update()
{
	Entity::Update();
}

void Thorn::Initialize(bool isLeft)
{
	if (isLeft)
	{
		this->SetReverse(false);
	}
	else
	{
		this->SetReverse(true);
	}
}

void Thorn::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
