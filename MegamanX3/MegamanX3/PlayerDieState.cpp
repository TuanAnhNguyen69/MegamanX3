#include "pch.h"
#include "PlayerDieState.h"
#include "Engine.h"

PlayerDieState::PlayerDieState(PlayerStateHandler * handler, Player * entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.75, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x_die",
		0, 7, 4, 250, 250);
	spriteLoopTimes = 0;
}

PlayerDieState::~PlayerDieState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Dying) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerDieState::Load()
{
	entity->SetSprite(sprite);
	sprite->ResetFrame();
}

void PlayerDieState::Update()
{
	if (sprite->GetCurrentFrame() >= 3) {
		sprite->SetFrameRange(3, 7);
	}

	if (sprite->IsFinished()) {
		spriteLoopTimes++;
	}

	if (spriteLoopTimes >= 20) {
		entity->RequireRevive();
		spriteLoopTimes = 0;
	}
}

void PlayerDieState::UpdateInput()
{

}
