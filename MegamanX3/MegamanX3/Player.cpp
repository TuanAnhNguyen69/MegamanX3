#include "pch.h"
#include "Player.h"
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
	entity->InitializeAnimatedSprite(device, "x", 15, 14, 23, 10, 50, 50);
	entity->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	entity->SetScale(2, 2);
}

void Player::Update()
{
	UpdateInput();
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
