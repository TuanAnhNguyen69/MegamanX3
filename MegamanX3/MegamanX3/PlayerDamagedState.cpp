#include "pch.h"
#include "PlayerDamagedState.h"
#include "Engine.h"

PlayerDamagedState::PlayerDamagedState(PlayerStateHandler *handler, Player *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 4, false);
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
	entity->SetImmute(true);
}

void PlayerDamagedState::Update()
{
	if (sprite->IsFinished()) {
		handler->ChangeState(PlayerStateHandler::StateName::Falling);
	}
}

void PlayerDamagedState::UpdateInput()
{
	
}

void PlayerDamagedState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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

