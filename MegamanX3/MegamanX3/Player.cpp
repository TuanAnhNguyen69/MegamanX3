#include "pch.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include <iostream>

Player::Player()
{
	entity = nullptr;
}


Player::~Player()
{
}

void Player::Initialize(LPDIRECT3DDEVICE9 device)
{
	entity = EntityManager::GetInstance()->AddEntity();
	entity->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	entity->SetScale(2, 2);

	standingState = new PlayerStandingState(this, entity);
	runningState = new PlayerRunningState(this, entity);

	ChangeState(Standing);
}

void Player::Update()
{
	if (currentState) {
		currentState->Update();
		currentState->UpdateInput();
	}
}

void Player::UpdateInput()
{
	entity->SetVelocity(0, 0);
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_W)) {
		entity->SetVelocity(0.0f, -150.0f);
	}

	if (input->IsKeyDown(DIK_S)) {
		entity->SetVelocity(0.0f, 150.0f);
	}

	if (input->IsKeyDown(DIK_D)) {
		entity->SetReverse(false);
		entity->SetVelocity(150.0f, 0.0f);
	}

	if (input->IsKeyDown(DIK_A)) {
		entity->SetReverse(true);
		entity->SetVelocity(-150.0f, 0.0f);
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
		break;
	case Running:
		currentState = runningState;
		break;
	}
	currentState->Load();
}

PlayerStateHandler::MoveDirection Player::GetMoveDirection() {
	return PlayerStateHandler::MoveDirection::None;
}
