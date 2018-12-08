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

void Map::Initialize(LPCTSTR fileName)
{
	std::string objFilePath("Map/");
	objFilePath.append(fileName).append("OBJ.txt");
	std::string mapFilePath("Map/");
	mapFilePath.append(fileName).append(".txt");

	std::ifstream map(mapFilePath);
	if (map.is_open())
	{

	}
	std::ifstream objects(objFilePath);
	quadTree = new QuadTree(1, { 0, 0, 7936, 2048 });
	std::cout << objects.is_open();

	if (objects.is_open())
	{
		float posX, posY; int width, height;
		int count;
		objects >> count;
		std::cout << count;
		for (int i = 0; i < count; i++)
		{
			float enumValue;
			int id;
			objects >> id >> posX >> posY >> width >> height;
			EntityId entityId = (EntityId)id;
			Entity *entity = EntityManager::GetInstance()->AddEntity(entityId);
			entity->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
				this->GetTextureName(entityId), width, height);
			entity->SetPosition(posX + width/2, posY + height/2);			
			quadTree->Insert(entity);
		}
	}
}

void Map::Update()
{
}

void Map::Render()
{
}

int Map::GetWidth()
{
	return 7936;
}

int Map::GetHeight()
{
	return 2048;
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

LPCTSTR Map::GetTextureName(EntityId entityId)
{
	switch (entityId)
	{
	case EntityId::Megaman:
		break;
	case EntityId::BlastHornet:
		break;
	case EntityId::Byte:
		break;
	case EntityId::Shurikein:
		break;
	case EntityId::CarryArm:
		break;
	case EntityId::HeadGunner:
		break;
	case EntityId::Helit:
		break;
	case EntityId::NotorBanger:
		break;
	case EntityId::Bee:
		break;
	case EntityId::Door:
		break;
	case EntityId::Ladder:
		break;
	case EntityId::Thorn:
		break;
	case EntityId::Box:
		break;
	case EntityId::Roof:
		break;
	case EntityId::BreakPlatform:
		break;
	case EntityId::Canon:
		break;
	case EntityId::GunnerRocket:
		break;
	case EntityId::HeliRocket:
		break;
	case EntityId::ByteBomb:
		break;
	case EntityId::SmallEnergy:
		break;
	case EntityId::BigEnergy:
		break;
	case EntityId::ChimeraArmor:
		break;
	case EntityId::MegamanBullet:
		break;
	case EntityId::Cargo:
		break;
	case EntityId::BigElevator:
		break;
	case EntityId::SmallElevator:
		break;
	case EntityId::BoxWall:
		break;
	case EntityId::UpGround:
		break;
	case EntityId::DownGround:
		break;
	case EntityId::Platform:
		return "PlayerPaper";
		break;
	case EntityId::BlueConveyor:
		break;
	case EntityId::YellowConveyor:
		break;
	case EntityId::SmallConveyor:
		break;
	default:
		return "PlayerPaper";
		break;
	}
}
