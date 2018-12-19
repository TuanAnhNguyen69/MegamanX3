#include "pch.h"
#include "EntityManager.h"
#include <iostream>
#include "EntityImport.h"
#include "Collision.h"

EntityManager *EntityManager::instance = nullptr;

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	RemoveAllEntities();
	if (quadTree) {
		delete quadTree;
		quadTree = nullptr;
	}
}

void EntityManager::Update()
{
	std::vector<Entity*> collidableEntity;
	quadTree->GetEntitiesCollideAble(collidableEntity, player);
	int size = collidableEntity.size();
	for (int index = 0; index < size; index++) {
		if (camera) {
			collidableEntity[index]->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
				SCREEN_HEIGHT / 2 - camera->GetCenter().y);
		}
		collidableEntity[index]->Update();
	}
}

void EntityManager::Render()
{
	std::vector<Entity*> collidableEntity;
	quadTree->GetEntitiesCollideAble(collidableEntity, player);
	int size = collidableEntity.size();
	for (int index = 0; index < size; index++) {
		collidableEntity[index]->Render();
	}
}

void EntityManager::CheckCollide()
{
	std::vector<Entity*> collidableEntity;
	EntityManager::GetInstance()->GetQuadTree()->GetEntitiesCollideAble(collidableEntity, player);
	for (size_t index = 0; index < collidableEntity.size(); index++) {
		for (size_t otherIndex = 0; otherIndex < collidableEntity.size(); otherIndex++) {
			if (index != otherIndex) {
				RECT broadphase = Collision::GetSweptBroadphaseRect(collidableEntity.at(index));
				if (Collision::IsCollide(broadphase, collidableEntity.at(otherIndex)->GetBound()))
				{
					Entity::CollisionReturn collideData;
					float collisionTime = Collision::SweptAABB(collidableEntity.at(index), collidableEntity.at(otherIndex), collideData);
					if (collisionTime < 1.0f) //collisiontime > 0 &&
					{
						Entity::CollisionSide entitySide = Collision::GetSideCollision(collidableEntity.at(index), collideData);
						Entity::CollisionSide impactorSide = Collision::GetSideCollision(collidableEntity.at(otherIndex), collideData);

						collidableEntity.at(index)->OnCollision(collidableEntity.at(otherIndex), entitySide, collideData);
						collidableEntity.at(otherIndex)->OnCollision(collidableEntity.at(index), impactorSide, collideData);
					}
				}
			}
		}
	}
}

int EntityManager::AddEntity(Entity * entity)
{
	entities.push_back(entity);
	return entities.size() - 1;
}

void EntityManager::RemoveEntity(Entity * entity)
{
	if (entity == nullptr) {
		return;
	}

	int index = -1;
	if (ContainsEntity(entity, index)) {
		entities.erase(entities.begin() + index);
		delete entity;
	}
}

void EntityManager::RemoveAllEntities()
{
	while (!entities.empty()) {
		Entity *entity = entities[0];
		entities.erase(entities.begin());
		delete entity;
	}
}

bool EntityManager::ContainsEntity(Entity * entity)
{
	int size = entities.size();
	for (int index = 0; index < size; index++) {
		if (entities[index] == entity) {
			return true;
		}
	}
	return false;
}

bool EntityManager::ContainsEntity(Entity * entity, int &entityIndex)
{
	entityIndex = -1;
	int size = entities.size();
	for (int index = 0; index < size; index++) {
		if (entities[index] == entity) {
			entityIndex = index;
			return true;
		}
	}
	return false;
}

EntityManager * EntityManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new EntityManager();
	}
	return instance;
}

void EntityManager::Initialize(Player *player, Camera * camera, LPCTSTR fileName, int mapWidth, int mapHeight)
{
	this->player = player;
	this->camera = camera;
	quadTree = new QuadTree(1, { 0, 0,mapWidth, mapHeight });
	LoadQuadtree(fileName);
}

std::vector<Entity*> EntityManager::GetAllEntities()
{
	return entities;
}

void EntityManager::LoadQuadtree(LPCTSTR filePath)
{
	std::string objFilePath("Map/");
	objFilePath.append(filePath).append("OBJ.txt");
	std::ifstream objects(objFilePath);

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
			switch (entityId)
			{
				/*	case EntityId::Megaman:
						break;
					case EntityId::BlastHornet:
						break;
					case EntityId::Byte:
						break;
					case EntityId::Shurikein:
						break;
					case EntityId::CarryArm:
						break;*/
			case EntityId::HeadGunner_ID:
			{
				/*HeadGunner * headGunner = new HeadGunner(this->player);
				headGunner->Initialize();
				headGunner->SetPosition(posX + width / 2, posY + height / 2);
				headGunner->SetScale(2, 2);
				headGunner->SetBound(width, height);
				AddEntity(headGunner);
				break;*/
				/*NotorBanger * notoBanger = new NotorBanger(player);
				notoBanger->Initialize();
				notoBanger->SetPosition(posX + width / 2, posY + height / 2);
				notoBanger->SetScale(2, 2);
				notoBanger->SetBound(width, height);
				AddEntity(notoBanger);
				break;*/

				Helit * helit = new Helit(player);
				helit->Initialize();
				helit->SetPosition(posX + width / 2, posY + height / 2);
				helit->SetScale(2, 2);
				helit->SetBound(width, height);
				AddEntity(helit);
				break;
			}

			case EntityId::NotorBanger_ID:
			{
				NotorBanger * notoBanger = new NotorBanger(player);
				notoBanger->Initialize();
				notoBanger->SetPosition(posX + width / 2, posY + height / 2);
				notoBanger->SetScale(2, 2);
				notoBanger->SetBound(width, height);
				AddEntity(notoBanger);
				break;
			}
			/*case EntityId::Bee:
				break;
				case EntityId::Helit:
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
				break;*/
			case EntityId::Platform_ID:
			{
				Platform * platform = new Platform();
				platform->SetPosition(posX + width / 2, posY + height / 2);
				platform->SetBound(width, height);
				platform->Initialize();
				AddEntity(platform);
				break;
			}

			/*case EntityId::BlueConveyor:
				break;
			case EntityId::YellowConveyor:
				break;
			case EntityId::SmallConveyor:
				break;*/
			default:
			{
				Platform * platform = new Platform();
				platform->SetPosition(posX + width / 2, posY + height / 2);
				platform->SetBound(width, height);
				platform->Initialize();
				AddEntity(platform);
				break;
			}
			}
		}

		for (auto child : GetAllEntities()) {
			quadTree->Insert(child);
		}
		int a = 0;
	}
}

QuadTree * EntityManager::GetQuadTree()
{
	return quadTree;
}