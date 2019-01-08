#include "pch.h"
#include "Canon.h"



Canon::Canon(Player *player) : Enemy(EntityId::Canon_ID, player)
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"canon", 9, 9);
	sprite = new AnimatedSprite(10, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "canon",
		0, 0, 1, 9, 9);
}


Canon::~Canon()
{
}

void Canon::Initialize(bool isHigh, bool isLeft)
{
	this->damage = 1;
	this->isHigh = isHigh;
	this->isLeft = isLeft;
	this->hitted = false;

	if (!isHigh)
	{
		this->SetVelocityY(-Define::CANON_MAX_LOW_VELOCITY_Y);
	}
	else
	{
		this->SetVelocityY(-Define::CANON_MAX_LOW_VELOCITY_Y);
	}
	if (isLeft)
	{
		this->SetVelocityX(-Define::CANON_MAX_VELOCITY_X);
	}
	else
	{
		this->SetVelocityX(Define::CANON_MAX_VELOCITY_X);
	}
}

void Canon::Update()
{
	if (this->hitted) {
		if (sprite->IsFinished()) {
			EntityManager::GetInstance()->RemoveEntity(this);
			return;
		}
	}
	else {
		if (!isHigh)
		{
			this->AddVelocityY(Define::CANON_LOW_VELOCITY_Y);
			if (this->GetVelocity().y > 0)
			{
				this->AddVelocityY(10.0f);
			}
		}
		else
		{
			this->AddVelocityY(Define::CANON_HIGH_VELOCITY_Y);
			if (this->GetVelocity().y > 0)
			{
				this->AddVelocityY(10.0f);
			}
		}

		if (isLeft)
		{
			this->AddVelocityX(-Define::CANON_VELOCITY_X);
			if (this->GetVelocity().x < 0)
			{
				this->AddVelocityX(15.0f);
			}
		}
		else
		{
			this->AddVelocityX(Define::CANON_VELOCITY_X);
			if (this->GetVelocity().x < 0)
			{
				this->AddVelocityX(-15.0f);
			}
		}
	}
	
	//this->AddVelocityY(-10.0f);
	Entity::Update();
	//float dt = Timer::GetDeltaTime();

	//this->SetPosition(this->GetVelocity().x * dt, this->GetPosition().y);

	//float dx = x0 - this->GetPosition().x;

	//float relaHeight = 0.03f;			//chiều cao tương dối: càng lớn thấp (rớt nhanh hơn)
	//float relaDistance = 4.0f;			//chiều xa tương đối : càng lớn xa 

	//this->SetPosition(this->GetVelocity().x, -relaHeight*(dx*dx) + relaDistance*dx + y0);
}



void Canon::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

	if (!this->hitted) {
		if (!(impactor->GetEntityId() == EntityId::NotorBanger_ID 
			|| impactor->GetEntityId() == EntityId::LeftFaceHeadGunner_ID
			|| impactor->GetEntityId() == EntityId::RightFaceHeadGunner_ID 
			|| impactor->GetEntityId() == EntityId::Canon_ID)) {

			if (impactor->GetEntityId() == EntityId::Megaman_ID && ((Player *)impactor)->IsImmute()) {
				return;
			}
			this->SetVelocity(0, 0);
			sprite = new AnimatedSprite(15, 1, false);
			sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
				0, 7, 8, 50, 50);
			this->SetSprite(sprite);
			Sound::getInstance()->loadSound((char*)"sound/explosion.wav", "explosion_canon");
			Sound::getInstance()->play("explosion_canon", false, 1);
			this->hitted = true;
		}
	}
	
	return;
}

bool Canon::IsHitted() {
	return this->hitted;
}

