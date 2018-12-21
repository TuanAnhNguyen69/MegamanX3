#include "pch.h"
#include "HelitRocket.h"


HelitRocket::HelitRocket() : Entity(EntityId::GunnerRocket_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"helit_rocket", 20, 14);
	sprite = new AnimatedSprite(10, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit_rocket",
		0, 0, 1, 20, 14);
}


HelitRocket::~HelitRocket()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void HelitRocket::Initialize(bool isLeft)
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

void HelitRocket::Update()
{
	if (isLeft) {
		this->AddVelocityX(-10.0);
	}
	else {
		this->AddVelocityX(+10.0);
	}
	
	Entity::Update();
}



void HelitRocket::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}
