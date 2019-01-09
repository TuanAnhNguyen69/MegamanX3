#include "pch.h"
#include "HeadGunnerRocket.h"


HeadGunnerRocket::HeadGunnerRocket(Player *player) : Enemy(EntityId::GunnerRocket_ID, player)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"head_gunner_rocket", 25, 9);
	sprite = new AnimatedSprite(10, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner_rocket",
		0, 1, 2, 25, 9);
}


HeadGunnerRocket::~HeadGunnerRocket()
{
	
}

void HeadGunnerRocket::Initialize(bool isLeft)
{
	this->damage = 1;
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

void HeadGunnerRocket::Update()
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
			if (this->GetPosition().y > player->GetPosition().y) {
				this->AddVelocityY(-10.0f);
			}
			else {
				this->AddVelocityY(10.0f);
			}
		}
		else {
			this->AddVelocityX(+10.0);
			if (this->GetPosition().y > player->GetPosition().y) {
				this->AddVelocityY(-10.0f);
			}
			else {
				this->AddVelocityY(10.0f);
			}
		}
	}

	Entity::Update();
}

void HeadGunnerRocket::OnCollision(Entity * impactor,  Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (!hitted) {
		if (!(impactor->GetEntityId() == EntityId::LeftFaceHeadGunner_ID
			|| impactor->GetEntityId() == EntityId::RightFaceHeadGunner_ID
			|| impactor->GetEntityId() == EntityId::GunnerRocket_ID)) {

			if (impactor->GetEntityId() == EntityId::Megaman_ID && ((Player *)impactor)->IsImmute()) {
				return;
			}

			this->SetVelocityX(0);
			sprite = new AnimatedSprite(15, 1, false);
			sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
				0, 7, 8, 50, 50);
			this->SetSprite(sprite);
			Sound::getInstance()->play("explosion", false, 1);
			this->hitted = true;
		}
	}

}

bool HeadGunnerRocket::IsHitted()
{
	return this->hitted;
}
