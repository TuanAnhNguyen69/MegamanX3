#include "pch.h"
#include "HelitRocket.h"


HelitRocket::HelitRocket() : Entity(EntityId::Helit_ID)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"helit_rocket", 20, 14);
	sprite = new AnimatedSprite(10, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit_rocket",
		0, 0, 1, 20, 14);
}


HelitRocket::~HelitRocket()
{
	
}

void HelitRocket::Initialize(bool isLeft)
{
	this->hitted = false;
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
	if (this->hitted) {
		if (sprite->IsFinished()) {
			EntityManager::GetInstance()->RemoveEntity(this);
			return;
		}
	}
	else {
		if (isLeft) {
			this->AddVelocityX(-10.0);
		}
		else {
			this->AddVelocityX(+10.0);
		}
	}
	
	
	Entity::Update();
}



void HelitRocket::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if(!hitted){
		if (!(impactor->GetEntityId() == EntityId::Helit_ID || impactor->GetEntityId() == EntityId::HeliRocket_ID))
		{
			this->SetVelocityX(0);
			sprite = new AnimatedSprite(15, 1, false);
			sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
				0, 7, 8, 50, 50);
			this->SetSprite(sprite);
			this->hitted = true;
		}
		else {
			return;
		}
	}	
}

bool HelitRocket::IsHitted()
{
	return this->hitted;
}
