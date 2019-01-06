#include "pch.h"
#include "PlayerBullet.h"
#include "Engine.h"

PlayerBullet::PlayerBullet() : Entity(EntityId::MegamanBullet_ID)
{
}

void PlayerBullet::Initialize(int damage)
{
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
		break;
	case 3:
		if (sprite->GetCurrentFrame() > 1) {
			sprite->SetFrameRange(2, 8);
		}
	case 10:
		if (sprite->GetCurrentFrame() > 1) {
			sprite->SetFrameRange(2, 5);
		}
	}

	if (this->GetReverse()) {
		this->AddVelocityX(-10);
	}
	else {
		this->AddVelocityX(10);
	}

	Entity::Update();
}

void PlayerBullet::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

}

PlayerBullet::~PlayerBullet()
{
}