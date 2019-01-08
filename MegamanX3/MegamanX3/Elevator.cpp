#include "pch.h"
#include "Elevator.h"


Elevator::Elevator() : Entity(EntityId::BigElevator_ID)
{
	
}


Elevator::~Elevator()
{
}

void Elevator::Initialize()
{
	sprite = new AnimatedSprite(30, 0.5, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "elevator",
		0, 2, 3, 100, 45);

	active = false;
	this->SetSprite(sprite);
	this->SetVelocity(0, 0);
	this->speed = Define::ELEVATOR_SPEED;
	this->traveledDistance = 0;
}

void Elevator::Update()
{
	if (!active || traveledDistance >= Define::MAX_DISTANCE)
	{
		sprite->SetFrameRange(0, 0);
		this->AddPosition(0, 0);
	}
	else
	{
		sprite->SetFrameRange(0, 2);
		this->AddPosition(0, speed);
		traveledDistance += abs(speed);
	}

	Entity::Update();
}

int Elevator::GetSpeed()
{
	return speed;
}

bool Elevator::IsActive()
{
	return active;
}



void Elevator::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side) {
	case Top:
	case TopLeft:
	case TopRight:
		if (impactor->GetEntityId() == EntityId::Megaman_ID)
		{
			this->active = true;
		}
		break;
	}
	
}
