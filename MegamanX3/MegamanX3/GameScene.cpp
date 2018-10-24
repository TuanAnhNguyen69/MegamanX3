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
