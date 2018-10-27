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
}

void PlayerRunningState::Load()
{
	entity->SetSprite(sprite);
	acceleratorX = 25.0f;
}

void PlayerRunningState::Update()
{
}

void PlayerRunningState::UpdateInput()
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
	else {
		handler->ChangeState(PlayerStateHandler::StateName::Standing);
	}
}

