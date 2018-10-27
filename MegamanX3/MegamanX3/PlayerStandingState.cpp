#include "pch.h"
#include "PlayerStandingState.h"
#include "AnimatedSprite.h"
#include "Engine.h"

PlayerStandingState::PlayerStandingState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		7, 9, 10, 50, 50);
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
	sprite->SetFrameRange(7, 9);
}

void PlayerStandingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_J)) {
		sprite->SetFrameRange(10, 12);
	}

	if (input->IsKeyDown(DIK_D) || input->IsKeyDown(DIK_A)) {
		handler->ChangeState(PlayerStateHandler::StateName::Running);
	}
}

