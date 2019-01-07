#include "pch.h"
#include "Conveyor.h"


Conveyor::Conveyor(EntityId id) : Entity(id)
{
	switch (id)
	{
	case LeftYellowConveyor_ID:
		sprite = new AnimatedSprite(Define::CONVEYOR_SPEED, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "left_yellow_conveyor",
			0, 3, 1, 704, 64);
		speed = -Define::CONVEYOR_SPEED;
		break;
	case RightYellowConveyor_ID:
		sprite = new AnimatedSprite(Define::CONVEYOR_SPEED, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "right_yellow_conveyor",
			0, 3, 1, 672, 64);
		speed = Define::CONVEYOR_SPEED;
		break;
	case LeftBlueConveyor_ID:
		sprite = new AnimatedSprite(Define::CONVEYOR_SPEED, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "left_blue_conveyor",
			0, 3, 1, 352, 64);
		speed = -Define::CONVEYOR_SPEED;
		break;
	case RightBlueConveyor_ID:
		sprite = new AnimatedSprite(Define::CONVEYOR_SPEED, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "small_conveyor",
			0, 3, 1, 380, 64);
		speed = Define::CONVEYOR_SPEED;
		break;
	case RightSmallConveyor_ID:
		sprite = new AnimatedSprite(Define::CONVEYOR_SPEED, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "small_conveyor",
			0, 3, 1, 256, 64);
		this->SetReverse(true);
		speed = -Define::CONVEYOR_SPEED;
		break;
	case LeftSmallConveyor_ID:
		sprite = new AnimatedSprite(Define::CONVEYOR_SPEED, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "small_conveyor",
			0, 3, 1, 256, 64);
		this->SetReverse(false);
		speed = Define::CONVEYOR_SPEED;
		break;
	default:
		sprite = new AnimatedSprite(Define::CONVEYOR_SPEED, 1, true);
		sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "small_conveyor",
			0, 3, 1, 256, 64);
		this->SetReverse(true);
		speed = -Define::CONVEYOR_SPEED;
		break;
	}
}


Conveyor::~Conveyor()
{
}

void Conveyor::Initialize()
{
	this->SetSprite(sprite);
	this->SetVelocity(0, 0);
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
