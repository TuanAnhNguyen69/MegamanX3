#include "pch.h"
#include "PlayerStandingState.h"
#include "AnimatedSprite.h"
#include "Engine.h"

PlayerStandingState::PlayerStandingState(PlayerStateHandler *handler, Player *entity) : PlayerState(handler, entity)
{
	standSprite = new AnimatedSprite(15, 0.3, true);
	standSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		7, 9, 10, 50, 50);
	shootSprite = new AnimatedSprite(15, 0.7, true);
	shootSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		10, 12, 10, 50, 50);
	sprite = standSprite;
}

PlayerStandingState::~PlayerStandingState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerStandingState::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void PlayerStandingState::Update()
{

}

void PlayerStandingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_J)) {
		sprite = shootSprite;
		shooting = true;
		entity->SetSprite(sprite);
	}
	else {
		sprite = standSprite;
		entity->SetSprite(sprite);
	}

	if (input->IsKeyDown(DIK_D) || input->IsKeyDown(DIK_A)) {
		handler->ChangeState(PlayerStateHandler::StateName::Running);
	}
}

