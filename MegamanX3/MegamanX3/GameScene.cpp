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

	if (camera) {
		delete camera;
		camera = nullptr;
	}

	if (map) {
		delete map;
		map = nullptr;
	}
}

bool GameScene::Initialize()
{
	// 2695, -190
	map = new Map();
	map->Initialize("abc");

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetCenter(SCREEN_WIDTH / 2, map->GetHeight() - camera->GetHeight());

	player = new Player();
	player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice());
	player->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return true;
}

void GameScene::Update()
{
	camera->SetCenter(player->GetPosition());
	player->Update();
}

void GameScene::Render()
{
}
