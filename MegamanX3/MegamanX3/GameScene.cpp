#include "pch.h"
#include "GameScene.h"

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
		SCREEN_WIDTH, SCREEN_HEIGHT, 2800, 10);

	player = new Player();
	player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice());
	return true;
}

void GameScene::Update()
{
	player->Update();
}

void GameScene::Render()
{
}
