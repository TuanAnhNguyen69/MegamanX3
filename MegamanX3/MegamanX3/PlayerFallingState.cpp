#include "pch.h"
#include "PlayerFallingState.h"
#include "Engine.h"

PlayerFallingState::PlayerFallingState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		37, 40, 10, 50, 50);
}


PlayerFallingState::~PlayerFallingState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Falling) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerFallingState::Load()
{
	entity->SetSprite(sprite);
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;
	sprite->ResetFrame();
}

void PlayerFallingState::Update()
{
	sprite->SetFrameRange(37, 40);
	entity->AddVelocityY(acceleratorY);
	if (entity->GetVelocity().y > Define::PLAYER_MAX_JUMP_VELOCITY) {
		entity->SetVelocityY(Define::PLAYER_MAX_JUMP_VELOCITY);
	}

	// For testing
	if (entity->GetPosition().y > (SCREEN_HEIGHT / 2)) {
		handler->ChangeState(PlayerStateHandler::StateName::Standing);
	}
}

void PlayerFallingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_J)) {
		sprite->SetFrameRange(44, 47);
	}

	if (input->IsKeyDown(DIK_D)) {
		entity->SetReverse(false);
		if (entity->GetVelocity().x < Define::PLAYER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x >= Define::PLAYER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (input->IsKeyDown(DIK_A)) {
		entity->SetReverse(true);
		if (entity->GetVelocity().x > -Define::PLAYER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < -Define::PLAYER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
}
