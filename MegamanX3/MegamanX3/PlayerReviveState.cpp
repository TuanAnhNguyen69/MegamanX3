#include "pch.h"
#include "PlayerReviveState.h"
#include "Engine.h"

PlayerReviveState::PlayerReviveState(PlayerStateHandler * handler, Player * entity) : PlayerState(handler, entity)
{
	fallSprite = new AnimatedSprite(15, 0.5, false);
	fallSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		0, 0, 10, 50, 50);

	landSprite = new AnimatedSprite(15, 3, false);
	landSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		1, 6, 10, 50, 50);
}

PlayerReviveState::~PlayerReviveState()
{
}

void PlayerReviveState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID) {
		switch (side)
		{
		case Entity::Left:
		case Entity::Right:
		case Entity::Top:
			break;
		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				entity->SetVelocityY(0);
			}
			entity->blockType = Player::None;
			entity->isJumping = false;
			entity->SetSprite(landSprite);
			return;

		default:
			entity->blockType = Player::None;
			break;
		}
	}
}

void PlayerReviveState::Load()
{
	entity->SetSprite(fallSprite);
	entity->SetMovable(false);
	fallSprite->ResetFrame();
	landSprite->ResetFrame();
}

void PlayerReviveState::Update()
{
	if (landSprite->IsFinished()) {
		entity->ChangeState(PlayerStateHandler::StateName::Standing);
		return;
	}
	entity->AddVelocityY(23.0f);
}

void PlayerReviveState::UpdateInput()
{
}
