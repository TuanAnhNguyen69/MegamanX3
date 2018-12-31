#include "pch.h"
#include "Conveyor.h"


Conveyor::Conveyor(EntityId id) : Entity(id)
{
	this->speed = Define::CONVEYOR_SPEED;
	switch (id)
	{
	case LeftYellowConveyor_ID:
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
			"yellow_conveyor", 32, 32);
		sprite = new AnimatedSprite(speed, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "yellow_conveyor",
			0, 3, 4, 32, 32);
		this->SetBound(32 * 2, 32 * 2);
		break;
	case RightYellowConveyor_ID:
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
			"head_yellow_conveyor", 18, 32);
		sprite = new AnimatedSprite(speed, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_yellow_conveyor",
			0, 3, 4, 18, 32);
		this->SetBound(18 * 2, 32 * 2);
		break;
	case LeftBlueConveyor_ID:
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
			"blue_conveyor", 32, 32);
		sprite = new AnimatedSprite(speed, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blue_conveyor",
			0, 3, 4, 32, 32);
		this->SetBound(32 * 2, 32 * 2);
		break;
	case RightBlueConveyor_ID:
		this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
			"head_blue_conveyor", 18, 32);
		sprite = new AnimatedSprite(speed, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_blue_conveyor",
			0, 3, 4, 18, 32);
		this->SetBound(18 * 2, 32 * 2);
		break;
	}
}


Conveyor::~Conveyor()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void Conveyor::Initialize(bool isRunToLeft)
{
	this->SetSprite(sprite);
	this->SetVelocity(0, 0);
	if (isRunToLeft)
	{
		this->SetReverse(true);
		speed = -Define::CONVEYOR_SPEED;
	}
	else
	{
		this->SetReverse(false);
		speed = Define::CONVEYOR_SPEED;
	}
}

void Conveyor::Update()
{
	Entity::Update();
}

void Conveyor::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}

float Conveyor::GetSpeed()
{
	return speed;
}
