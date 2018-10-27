#include "pch.h"
#include "PlayerFallingState.h"
#include "Engine.h"

PlayerFallingState::PlayerFallingState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.4);
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
}

void PlayerFallingState::Update()
{
	entity->AddVelocityY(acceleratorY);
	if (entity->GetVelocity().y > 480.0f) {
		entity->SetVelocityY(480.0f);
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

	if (input->IsKeyDown(DIK_D)) {
		entity->SetReverse(false);
		if (entity->GetVelocity().x < 350.0f) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x >= 350.0f) {
				entity->SetVelocityX(350.0f);
			}
		}
	}
	else if (input->IsKeyDown(DIK_A)) {
		entity->SetReverse(true);
		if (entity->GetVelocity().x > -350.0f) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < -350.0f) {
				entity->SetVelocityX(-350.0f);
			}
		}
	}
}
