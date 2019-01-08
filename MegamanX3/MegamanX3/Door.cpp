#include "pch.h"
#include "Door.h"
#include "Engine.h"

Door::Door() : Entity(EntityId::Door_ID)
{
	
}


Door::~Door()
{
}

void Door::Update()
{
	if (state == DoorState::CLOSING) {
		SetSprite(closingSprite);
		if (closingSprite->GetCurrentFrame() == 1) {
			state = DoorState::CLOSED;
		}
	}

	if (state == DoorState::OPENNING) {
		SetSprite(openningSprite);
		if (openningSprite->GetCurrentFrame() == 15) {
			state = DoorState::OPENED;
		}
	}

	if (state == DoorState::CLOSED) {
		SetSprite(closedSprite);
	}

	if (state == DoorState::OPENED) {
		SetSprite(openedSprite);
	}

	Entity::Update();
}

void Door::Initialize()
{
	closedSprite = new AnimatedSprite(30, 0.3, false);
	closedSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "door",
		0, 0, 17, 64, 96);

	openningSprite = new AnimatedSprite(30, 0.3, false);
	openningSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "door",
		1, 16, 17, 64, 96);

	closingSprite = new AnimatedSprite(30, 0.3, false);
	closingSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "door",
		1, 16, 17, 64, 96);
	closingSprite->SetReverse(true);

	openedSprite = new AnimatedSprite(30, 0.3, false);
	openedSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "door",
		16, 16, 17, 64, 96);

	state = DoorState::CLOSED;
}

void Door::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Megaman_ID && side == CollisionSide::Left || side == CollisionSide::Right) {
		if (state == DoorState::OPENED) {
			return;
		}

		if (state == DoorState::CLOSED) {
			state = DoorState::OPENNING;
		}
	}
}

Door::DoorState Door::GetState()
{
	return this->state;
}

void Door::SetState(DoorState state)
{
	this->state = state;
}
