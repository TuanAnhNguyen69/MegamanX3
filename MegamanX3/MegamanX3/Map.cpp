#include "pch.h"
#include "Map.h"
#include "Engine.h"
#include "EntityImport.h"

Map::Map()
{
	quadTree = nullptr;
	tiles = new std::map<int, Tile*>();
}

Map::~Map()
{
	if (quadTree) {
		delete quadTree;
		quadTree = nullptr;
	}
}

void Map::Initialize(LPCTSTR fileName)
{
	LoadBackground(fileName);
}

void Map::Update()
{

}

void Map::RenderBackground(Camera *camera)
{
	if (backgroundSprite) {
		D3DXMATRIX transformMatrix;
		D3DXVECTOR2 scale = D3DXVECTOR2(2, 2);
		D3DXVECTOR2 translation = D3DXVECTOR2(SCREEN_WIDTH / 2 - camera->GetCenter().x,
			SCREEN_HEIGHT / 2 - camera->GetCenter().y);
		D3DXVECTOR2 center = D3DXVECTOR2(backgroundSprite->GetFrameWidth(), backgroundSprite->GetFrameHeight());
		D3DXMatrixTransformation2D(&transformMatrix, &center, 0.0f, &scale, nullptr, 0.0f, &translation);
		LPD3DXSPRITE spriteHandler = Engine::GetEngine()->GetSpriteHandler();
		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);
		spriteHandler->SetTransform(&transformMatrix);
		backgroundSprite->Render(D3DXVECTOR3(backgroundSprite->GetFrameWidth(), backgroundSprite->GetFrameHeight(), 0));
		spriteHandler->SetTransform(&oldMatrix);
	}
}

int Map::GetWidth()
{
	return this->GetTileWidth() * tilesColCount;
}

int Map::GetHeight()
{
	return this->GetTileHeight() * tilesRowCount;
}

int Map::GetTileWidth()
{
	return 32;
}

int Map::GetTileHeight()
{
	return 32;
}


void Map::LoadBackground(LPCTSTR fileName)
{
	std::string tilesImageFilePath("Map/");
	tilesImageFilePath.append(fileName).append(".png");
	ResourceManager::GetInstance()->LoadTextureResource(Engine::GetEngine()->GetGraphics()->GetDevice(), tilesImageFilePath.c_str());
	Texture * texture = ResourceManager::GetInstance()->GetTextureByName(std::string(fileName).c_str());
	backgroundSprite = new Sprite(texture->GetWidth(), texture->GetHeight(), 0.0f, 0.0f);
	backgroundSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), fileName);
	this->tilesColCount = texture->GetWidth() / 32;
	this->tilesRowCount = texture->GetHeight() / 32;

	/*std::string tilesFilePath("Map/");
	tilesFilePath.append(fileName).append(".txt");
	std::ifstream map(tilesFilePath);
	tiles->clear();
	if (map.is_open())
	{
		float posX, posY;
		int col, row;
		int count;
		map >> count;

		map >> row >> col;

		int tileID;
		int value = 0;
		for (int rowIndex = 1; rowIndex <= row; rowIndex++)
		{
			for (int colIndex = 1; colIndex <= col; colIndex++, value++) {
				map >> tileID;
				posX = (colIndex - 1) * 32;
				posY = (rowIndex - 1) * 32;
				tiles->insert(std::pair<int, Tile*>(value, new Tile(tileID, posX, posY)));
			}
		}
	}
	map.close();*/
}

std::list<int> * Map::GetAvailableTiles(RECT viewport)
{
	std::list<int> *currentTiles = new std::list<int>();
	int rowIndex = 1;
	int maxRowIndex = 1;
	int colIndex = 1;
	int maxColIndex = 1;

	if (viewport.top / 32 > 0) {
		rowIndex = (viewport.top / 32) + 1;
	}

	if (viewport.bottom / 32 > 0 && viewport.bottom / 32 <= this->tilesRowCount) {
		maxRowIndex = viewport.bottom / 32;
	}

	if (viewport.left / 32 > 0) {
		colIndex = viewport.left / 32 + 1;
	}

	if (viewport.right / 32 > 0 && viewport.right / 32 <= this->tilesColCount) {
		maxColIndex = viewport.right / 32;
	}

	for (rowIndex; rowIndex <= maxRowIndex; rowIndex++) {
		for (int col = colIndex; col <= maxColIndex; col++) {
			currentTiles->push_back((rowIndex - 1) * tilesColCount + col - 1);
		}
	}

	return currentTiles;
}