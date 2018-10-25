#include "pch.h"
#include "GameScene.h"
#include <iostream>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	if (player) {
		delete player;
		player = nullptr;
	}
}

bool GameScene::Initialize()
{
	map = EntityManager::GetInstance()->AddEntity();
	map->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "stage",
		SCREEN_WIDTH, SCREEN_HEIGHT, 2695, -190);
	map->SetScale(2, 2);

	player = new Player();
	player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice());
	return true;
}

void GameScene::Update()
{
	player->Update();
	RECT bound = Engine::GetEngine()->GetCamera()->GetBound();
	std::cout << "Update map to: " << (-190 + bound.left) << ", " << (2695 + bound.top) << std::endl;
	map->SetSpritePosition(-190 + bound.left, 2695 + bound.top);
}

void GameScene::Render()
{
}
