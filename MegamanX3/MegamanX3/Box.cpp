#include "pch.h"
#include "Box.h"


Box::Box(EntityId id, Player *player) : Enemy(id, player)
{
	hadBurst = false;
	HP = 12;
	this->isFall = false;
	this->id = id;
	sprite = new AnimatedSprite(15, 1, false);
	switch (id)
	{
	case Box_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box", 72, 72);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 72, 72);
		this->SetBound(72, 72);
	}
	break;

	case DoubleBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box2", 144, 72);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box3",
			0, 0, 1, 144, 72);
		this->SetBound(144, 72);
	}
	break;
	case TrippleBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box3", 72, 216);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box3",
			0, 0, 1, 72, 216);
		this->SetBound(72, 216);
	}
	break;

	case QuadraBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box4", 72, 288);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box4",
			0, 0, 1, 72, 288);
		this->SetBound(72, 288);
	}
	break;

	case VerticalBombBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_vertical", 118, 144);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_vertical",
			0, 0, 1, 118, 144);
		this->SetBound(118, 144);

	}
	break;

	case HorizontalBombBox_ID:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_horizontal", 144, 96);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box_horizontal",
			0, 0, 1, 144, 96);
		this->SetBound(144, 96);
	}
	break;

	default:
	{
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "box", 72, 72);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "box",
			0, 0, 1, 50, 50);
		this->SetBound(50, 50);
	}
	break;
	}
	
}


Box::~Box()
{

}

void Box::Update()
{
	Entity::Update();
	if (this->isFall)
	{
		this->SetVelocityY(Define::BOX_SPEED);
	}

	if (HP <= 0)
	{
		if (!hadBurst)
		{
			//sprite = new AnimatedSprite(15, 1, false);
			switch (id)
			{
			case Box_ID:
				this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "die", 50, 50);
				sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
					0, 7, 8, 50, 50);
				break;
			case DoubleBox_ID:
			case HorizontalBombBox_ID:
				this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_2_horizontal", 100, 50);
				sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_2_horizontal",
					0, 7, 1, 100, 50);
				break;
			case TrippleBox_ID:
				this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_3_vertical", 50, 150);
				sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_3_vertical",
					0, 7, 8, 50, 150);
				break;
			case QuadraBox_ID:
				this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_4_vertical", 50, 200);
				sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_4_vertical",
					0, 7, 8, 50, 200);
				break;
			case VerticalBombBox_ID:
				this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_2_vertical", 50, 100);
				sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die_2_vertical",
					0, 8, 2, 100, 50);
				break;
			default:
				this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "die", 50, 50);
				sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "die",
					0, 7, 8, 50, 50);
				break;
			}
			this->SetSprite(sprite);
			this->SetScale(1.44, 1.44);
			Sound::getInstance()->loadSound((char*)"sound/explosion.wav", "explosion_die");
			Sound::getInstance()->play("explosion_die", false, 1);
			hadBurst = true;
		}
		if (sprite->IsFinished())
		{
			EntityManager::GetInstance()->RemoveEntity(this);
		}

		if (this->GetEntityId() == EntityId::Box_ID)
		{
			if (this->GetVelocity().y != 0)
			{
				this->damage = 1;
			}
			else
			{
				this->damage = 0;
			}
		}
	}
}

void Box::Initialize(bool isFall)
{
	this->isFall = isFall;
	this->SetVelocity(0, 0);
	isCollPlatform = false;
}

void Box::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID && this->id == EntityId::Box_ID)
	{
		switch (side)
		{
		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top + 1));
			this->SetVelocity(0, 0);
			this->isFall = false;
			this->isCollPlatform = true;
			break;
		}
		}
	}

	if (impactor->GetEntityId() == EntityId::MegamanBullet_ID)
	{
		if (this->GetHP() > 0 && !((PlayerBullet*)impactor)->IsHitted()) {
			this->SubHP(((PlayerBullet*)impactor)->GetDamage());
		}
	}
}

void Box::SetFall(bool isFall)
{
	this->isFall = isFall;
}

bool Box::IsFall()
{
	return this->isFall;
}

bool Box::IsCollisionPlatform()
{
	return this->isCollPlatform;
}

int Box::GetHP()
{
	return this->HP;
}

void Box::SubHP(int damage)
{
	HP -= damage;
}
