#include "pch.h"
#include "PlayerJumpingState.h"
#include "Engine.h"

PlayerJumpingState::PlayerJumpingState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.3);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x", 
		34, 36, 10, 50, 50);
}


PlayerJumpingState::~PlayerJumpingState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Jumping) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerJumpingState::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocityY(-480.0f);
	acceleratorX = 14.0f;
	acceleratorY = 15.0f;
	noPressed = false;
}

void PlayerJumpingState::Update()
{
	entity->AddVelocityY(acceleratorY);

	if (entity->GetVelocity().y >= 0) {
		handler->ChangeState(PlayerStateHandler::StateName::Falling);
		return;
	}

	if (noPressed) {
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveDirection::MoveToLeft) {
			if (entity->GetVelocity().x < 0) {
				entity->AddVelocityX(acceleratorX);
				if (entity->GetVelocity().x > 0) {
					entity->SetVelocityX(0);
				}
			}
		}
		else if (handler->GetMoveDirection() == PlayerStateHandler::MoveDirection::MoveToRight) {
			if (entity->GetVelocity().x > 0) {
				entity->AddVelocityX(-acceleratorX);
				if (entity->GetVelocity().x < 0) {
					entity->SetVelocityX(0);
				}
			}
		}
	}
}

void PlayerJumpingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_D)) {
		entity->SetReverse(false);
		if (entity->GetVelocity().x < 350.0f) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x >= 350.0f) {
				entity->SetVelocityX(350.0f);
			}
		}
		noPressed = false;
	}
	else if (input->IsKeyDown(DIK_A)) {
		entity->SetReverse(true);
		if (entity->GetVelocity().x > -350.0f) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < -350.0f) {
				entity->SetVelocityX(-350.0f);
			}
		}
		noPressed = false;
	}
	else {
		noPressed = true;
	}
}
