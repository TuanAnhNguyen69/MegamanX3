#include "pch.h"
#include "Bee.h"


Bee::Bee(Player *player) : Enemy(EntityId::Bee_ID, player)
{
	isFollow = true;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"bee", 30, 30);
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "bee",
		0, 2, 3, 30, 30);
	this->player = player;
}

Bee::Bee(Player *player, D3DXVECTOR3 desPos) : Enemy(EntityId::Bee_ID, player)
{
	isFollow = false;
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"bee", 30, 30);
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "bee",
		0, 2, 3, 30, 30);
	this->desPos = desPos;
}


Bee::~Bee()
{

}

void Bee::Initailize()
{
	damage = 1;
	this->hitted = false;
	timeBorn = clock();
	this->SetSprite(sprite);
	isStop = false;
	this->startPos = D3DXVECTOR3(this->GetPosition().x, this->GetPosition().y, 0);
}

void Bee::Update()
{
	if (this->hitted) {
		if (sprite->IsFinished()) {
			EntityManager::GetInstance()->RemoveEntity(this);
			return;
		}
	}
	else {
		timeCount = clock();
		int dt = (timeCount - timeBorn) / 1000;

		if (this->GetVelocity().x > 0)
		{
			this->SetReverse(false);
		}
		else if (this->GetVelocity().x < 0)
		{
			this->SetReverse(true);
		}

		if (isFollow)
		{
			this->Follow();

			if (dt > 3)
			{
				EntityManager::GetInstance()->RemoveEntity(this);
				return;
			}
		}
		else
		{
			if (!isStop)
				this->GoOn(desPos);
			else
				this->SetVelocity(0, 0);

			if (dt > 6)
			{
				EntityManager::GetInstance()->RemoveEntity(this);
				return;
			}
		}

		

		
	}

	Enemy::Update();
}

void Bee::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{

	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			this->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			isStop = true;
			break;
		}

		case Entity::Right:
		{
			this->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			isStop = true;
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{
			this->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			isStop = true;
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			isStop = true;
			break;
		}
		}
	}

	if (!this->hitted) {
		if (impactor->GetEntityId() == EntityId::Megaman_ID) {

			this->SetVelocity(0, 0);
			sprite = new AnimatedSprite(15, 1, false);
			sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
				0, 7, 8, 50, 50);
			this->SetSprite(sprite);
			Sound::getInstance()->play("explosion", false, 1);
			this->hitted = true;
		}
	}

}

void Bee::GoOn(D3DXVECTOR3 desPoint)
{
	D3DXVECTOR3 moveVector = D3DXVECTOR3(desPoint.x - startPos.x, desPoint.y - startPos.y, 0);

	float moveVectorSize = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

	this->AddVelocityX(moveVector.x / moveVectorSize * Define::BEE_SPEED);
	this->AddVelocityY(moveVector.y / moveVectorSize * Define::BEE_SPEED);
}

void Bee::Follow()
{
	D3DXVECTOR3 moveVector = D3DXVECTOR3(player->GetPosition().x - this->GetPosition().x,
		player->GetPosition().y - this->GetPosition().y, 0);

	float moveVectorSize = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

	this->AddVelocityX(moveVector.x / moveVectorSize * Define::BEE_FOLLOW_SPEED);
	this->AddVelocityY(moveVector.y / moveVectorSize * Define::BEE_FOLLOW_SPEED);
}

bool Bee::IsHitted()
{
	return this->hitted;
}


