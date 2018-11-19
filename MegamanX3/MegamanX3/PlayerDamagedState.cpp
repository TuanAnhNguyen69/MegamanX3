#include "pch.h"
#include "PlayerDamagedState.h"


#include "Engine.h"

PlayerDamagedState::PlayerDamagedState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		77, 85, 10, 50, 50);
}


PlayerDamagedState::~PlayerDamagedState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Damaged) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerDamagedState::Load()
{
	entity->SetSprite(sprite);
	sprite->ResetFrame();
}

void PlayerDamagedState::Update()
{
	if (sprite->IsFinished()) {
		handler->ChangeState(PlayerStateHandler::StateName::Standing);
	}
}

void PlayerDamagedState::UpdateInput()
{
	
}

void PlayerDamagedState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

		entity->SetVelocityY(0);

		return;
	}
	default:
		break;
	}
}

