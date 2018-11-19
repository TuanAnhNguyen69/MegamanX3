#include "pch.h"
#include "Map.h"
#include "EntityManager.h"
#include "Engine.h"

Map::Map()
{
	quadTree = nullptr;
}


Map::~Map()
{
	if (quadTree) {
		delete quadTree;
		quadTree = nullptr;
	}
}

void Map::Initialize(LPCTSTR filePath)
{
	quadTree = new QuadTree(1, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

	Entity *entity = EntityManager::GetInstance()->AddEntity();
	entity->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"PlayerPaper", 500, 86, 0, 0);
	//entity->SetScale(2, 2);
	entity->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100);

	quadTree->Insert(entity);
}

void Map::Update()
{
}

void Map::Render()
{
}

int Map::GetWidth()
{
	return 32 * 100;
}

int Map::GetHeight()
{
	return 32 * 100;
}

int Map::GetTileWidth()
{
	return 32;
}

int Map::GetTileHeight()
{
	return 32;
}

QuadTree * Map::GetQuadTree()
{
	return quadTree;
}
