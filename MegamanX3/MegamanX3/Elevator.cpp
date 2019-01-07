#include "pch.h"
#include "Elevator.h"


Elevator::Elevator() : Entity(EntityId::BigElevator_ID)
{
	
}


Elevator::~Elevator()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void Elevator::Initialize(float stopPointX, float stopPointY)
{
	sprite = new AnimatedSprite(30, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "elevator",
		0, 2, 3, 100, 45);

	stopPoint = D3DXVECTOR3(stopPointX, stopPointY, 0);
	isAction = false;
	this->SetSprite(sprite);
	this->SetVelocity(0, 0);
}

void Elevator::Update()
{
	if (!isAction || (this->GetPosition().x == stopPoint.x && this->GetPosition().y == stopPoint.y))
	{
		sprite->SetFrameRange(0, 0);
		this->SetVelocity(0, 0);
	}
	else
	{
		sprite->SetFrameRange(0, 3);
		this->SetVelocityY(Define::ELEVATOR_SPEED);
	}
}



void Elevator::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Megaman_ID)
	{
		this->isAction = true;
	}
}
