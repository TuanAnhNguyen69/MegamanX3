#include "pch.h"
#include "HeadGunnerRocket.h"


HeadGunnerRocket::HeadGunnerRocket(bool isLeft, bool isTop) : Entity(EntityId::GunnerRocket_ID)
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

void HeadGunnerRocket::Initialize()
{
	this->SetVelocity(-300.0,0.0);
	this->SetSprite(sprite);
}

void HeadGunnerRocket::Update()
{
	this->AddVelocityX(-10.0);
	Entity::Update();
}



void HeadGunnerRocket::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
