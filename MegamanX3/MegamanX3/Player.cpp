#include "pch.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"
#include <iostream>

Player::Player()
{
	entity = nullptr;
	currentState = nullptr;
	standingState = nullptr;
	runningState = nullptr;
}


Player::~Player()
{
	if (standingState) {
		delete standingState;
		standingState = nullptr;
	}

	if (runningState) {
		delete runningState;
		runningState = nullptr;
	}
}

void Player::Initialize(LPDIRECT3DDEVICE9 device)
{
	entity = EntityManager::GetInstance()->AddEntity();
	entity->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	entity->SetScale(2, 2);

	standingState = new PlayerStandingState(this, entity);
	runningState = new PlayerRunningState(this, entity);
	jumpingState = new PlayerJumpingState(this, entity);
	fallingState = new PlayerFallingState(this, entity);

	ChangeState(Standing);
	allowJump = true;
}

void Player::Update()
{
	if (currentState) {
		currentState->Update();
		currentState->UpdateInput();
	}

	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_SPACE)) {
		if (allowJump) {
			if (currentStateName == Running || currentStateName == Standing) {
				ChangeState(Jumping);
			}
			allowJump = false;
		}
	}
	
	if (input->IsKeyHit(DIK_SPACE)) {
		allowJump = true;
	}
}

void Player::SetPosition(int x, int y)
{
	entity->SetPosition(x, y);
}

D3DXVECTOR3 Player::GetPosition()
{
	return entity->GetPosition();
}

PlayerStateHandler::StateName Player::GetCurrentStateName() {
	return this->currentStateName;
}

void Player::ChangeState(PlayerStateHandler::StateName stateName) {
	switch (stateName) {
	case Standing:
		currentState = standingState;
		currentStateName = Standing;
		break;
	case Running:
		currentState = runningState;
		currentStateName = Running;
		break;
	case Jumping:
		currentState = jumpingState;
		currentStateName = Jumping;
		break;
	case Falling:
		currentState = fallingState;
		currentStateName = Falling;
		break;
	}
	currentState->Load();
}

PlayerStateHandler::MoveDirection Player::GetMoveDirection() {
	if (entity->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (entity->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}
