#include "pch.h"
#include "Player.h"


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
	entity->InitializeAnimatedSprite(device, "mario-shell-sprite", 15, 3, 3, 85, 64);
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

	if (input->IsKeyDown(DIK_D)) {
		entity->SetVelocity(150.0f, 0.0f);
	}

	if (input->IsKeyDown(DIK_A)) {
		entity->SetVelocity(-150.0f, 0.0f);
	}
}
