#include "pch.h"
#include "PlayerBullet.h"
#include "Engine.h"
#include "Enemy.h"

PlayerBullet::PlayerBullet() : Entity(EntityId::MegamanBullet_ID)
{

}

void PlayerBullet::Initialize(int damage)
{
	this->hitted = false;
	this->damage = damage;

	sprite = new AnimatedSprite(15, 1, true);
	switch (damage) {
	case 2:
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "normal_bullet",
			0, 0, 4, 46, 24);
		break;
	case 3:
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "super_bullet",
			0, 8, 16, 46, 24);
		break;
	case 10:
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "extreme_bullet",
			0, 5, 13, 46, 32);
		break;
	}

	this->SetSprite(sprite);
}

void PlayerBullet::Update()
{
	switch (damage) {
	case 2:
		if (hitted) {
			sprite->SetFrameRange(1, 3);
		}
		
		break;

	case 3:
		if (hitted) {
			sprite->SetFrameRange(9, 15);
		}
		else {
			if (sprite->GetCurrentFrame() > 1) {
				sprite->SetFrameRange(2, 8);
			}
		}
		
	case 10:
		if (hitted) {
			sprite->SetFrameRange(6, 12);
		}
		else {
			if (sprite->GetCurrentFrame() > 1) {
				sprite->SetFrameRange(2, 5);
			}
		}
	
	}


	if (hitted) {
		
		if (sprite->IsFinished()) {
			EntityManager::GetInstance()->RemoveEntity(this);
			return;
		}		
	}
	else
	{
		if (this->GetReverse()) {
			this->AddVelocityX(-20);
		}
		else {
			this->AddVelocityX(20);
		}
	}


	Entity::Update();
}

void PlayerBullet::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (impactor->GetEntityId()) {
	case EntityId::Shurikein_ID:
	case EntityId::Byte_ID:
	case EntityId::BlastHornet_ID:
	case EntityId::Helit_ID:
	case EntityId::NotorBanger_ID:
	case EntityId::RightFaceHeadGunner_ID:
	case EntityId::LeftFaceHeadGunner_ID:
	case EntityId::Box_ID:
	case EntityId::DoubleBox_ID:
	case EntityId::TrippleBox_ID:
	case EntityId::QuadraBox_ID:
	case EntityId::VerticalBombBox_ID:
	case EntityId::HorizontalBombBox_ID:
	{
		if (impactor->GetEntityId() != EntityId::Megaman_ID && impactor->GetEntityId() != EntityId::MegamanBullet_ID) {
			this->SetVelocityX(0);
			Sound::getInstance()->loadSound((char*)"sound/explosion.wav", "explosion_bullet");
			Sound::getInstance()->play("explosion_bullet", false, 1);

			if (!hitted) {
				((Enemy *)impactor)->SubHP(damage);
			}
			this->hitted = true;
		}
	}
	default:
		break;

	}
}

bool PlayerBullet::IsHitted()
{
	return hitted;
}

int PlayerBullet::GetDamage()
{
	return this->damage;
}

PlayerBullet::~PlayerBullet()
{
}