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
	entity->InitializeAnimatedSprite(device, "mario-shell-sprite", 15, 3, 3, 64, 64);
	entity->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void Player::Update()
{
	UpdateInput();
	D3DXVECTOR3 position = entity->GetPosition();
	std::cout << "Update camera to: " << position.x << ", " << position.y << std::endl;
	Engine::GetEngine()->GetCamera()->SetCenter(entity->GetPosition());
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
		entity->SetReverse(true);
		entity->SetVelocity(150.0f, 0.0f);
	}

	if (input->IsKeyDown(DIK_A)) {
		entity->SetReverse(false);
		entity->SetVelocity(-150.0f, 0.0f);
	}
}
