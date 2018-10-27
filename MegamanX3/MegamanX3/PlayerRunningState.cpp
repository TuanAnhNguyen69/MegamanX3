#include "pch.h"
#include "PlayerRunningState.h"
#include "Engine.h"

PlayerRunningState::PlayerRunningState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		14, 23, 10, 50, 50);
}


PlayerRunningState::~PlayerRunningState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Running) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerRunningState::Load()
{
	entity->SetSprite(sprite);
	acceleratorX = 25.0f;
}

void PlayerRunningState::Update()
{
	sprite->SetFrameRange(14, 23);
}

void PlayerRunningState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_J)) {
		sprite->SetFrameRange(24, 33);
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
	else {
		handler->ChangeState(PlayerStateHandler::StateName::Standing);
	}
}

