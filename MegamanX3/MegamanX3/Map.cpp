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
	std::ifstream map(filePath);

	if (map.is_open())
	{
		float posX, posY; int width, height;
		int count;
		map >> count;
		int id;
		int x = 0;


		// duyệt từng dòng của file Stage
		for (int i = 0; i < count; i++)
		{
			float enumValue;
			map >> id >> posX >> posY >> width >> height;
			//posY = G_MapHeight - posY - 16;
			if (id > 20) {
				int a = 0;
			}
			// ứng với giá trị value tương ứng để khởi tạo các object tương tứng
			switch (id)
			{

			}
		}
	}

	quadTree = new QuadTree(1, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

	Entity *entity = EntityManager::GetInstance()->AddEntity(EntityId::Platform);
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
