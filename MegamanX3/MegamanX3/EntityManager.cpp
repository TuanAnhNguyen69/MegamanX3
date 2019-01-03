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
	quadTree->Update();
	std::vector<Entity*> collidableEntity;
	quadTree->GetEntitiesCollideAble(collidableEntity, camera->GetBound());

	int size = collidableEntity.size();
	for (int index = 0; index < size; index++) {
		if (Collision::IsCollide(collidableEntity[index]->GetBound(), camera->GetBound())) {
			if (camera) {
				collidableEntity[index]->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
					SCREEN_HEIGHT / 2 - camera->GetCenter().y);
			}

			if (collidableEntity[index]->entityId == Canon_ID) {
				int a = 0;
			}

			collidableEntity[index]->Update();
		}
	}
}

void EntityManager::Render()
{
	std::vector<Entity*> collidableEntity;
	quadTree->GetEntitiesCollideAble(collidableEntity, camera->GetBound());
	int size = collidableEntity.size();
	for (int index = 0; index < size; index++) {
		if (collidableEntity[index]->entityId == Canon_ID) {
			int a = 0;
		}
		collidableEntity[index]->Render();
	}
}

void EntityManager::CheckCollide()
{
	std::vector<Entity*> playerCollidableEntity;
	quadTree->GetEntitiesCollideAble(playerCollidableEntity, camera->GetBound());
	for (size_t index = 0; index < playerCollidableEntity.size(); index++) {
		std::vector<Entity*> collidableEntity;
		quadTree->GetEntitiesCollideAble(collidableEntity, playerCollidableEntity.at(index)->GetBound());
		for (size_t otherIndex = 0; otherIndex < collidableEntity.size(); otherIndex++) {
			if (playerCollidableEntity.at(index) == collidableEntity.at(otherIndex)) {
				continue;
			}

			RECT broadphase = Collision::GetSweptBroadphaseRect(playerCollidableEntity.at(index));
			if (Collision::IsCollide(broadphase, collidableEntity.at(otherIndex)->GetBound()))
			{
				Entity::CollisionReturn collideData;
				float collisionTime = Collision::SweptAABB(playerCollidableEntity.at(index), collidableEntity.at(otherIndex), collideData);
				if (collisionTime < 1.0f) //collisiontime > 0 &&
				{
					Entity::CollisionSide entitySide = Collision::GetSideCollision(playerCollidableEntity.at(index), collideData);
					Entity::CollisionSide impactorSide = Collision::GetSideCollision(collidableEntity.at(otherIndex), collideData);

					playerCollidableEntity.at(index)->OnCollision(collidableEntity.at(otherIndex), entitySide, collideData);
					collidableEntity.at(otherIndex)->OnCollision(playerCollidableEntity.at(index), impactorSide, collideData);
				}
			}
		}
	}
}

int EntityManager::AddEntity(Entity * entity)
{
	entities.push_back(entity);
	quadTree->InsertEntity(entity);
	return entities.size() - 1;
}

void EntityManager::RemoveEntity(Entity * entity)
{
	if (entity == nullptr) {
		return;
	}

	if (!quadTree->RemoveEntity(entity)) {
		return;
	}

	int index = -1;
	if (ContainsEntity(entity, index)) {
		entities.erase(entities.begin() + index);
	}

	delete entity;
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
				headGunner->Initialize(true);
				headGunner->SetPosition(posX + width / 2, posY + height / 2);
				headGunner->SetScale(2, 2);
				headGunner->SetBound(width, height);
				AddEntity(headGunner);
				break;*/

				/*CarryArm * carryArm = new CarryArm(player);
				carryArm->Initialize();
				carryArm->SetPosition(posX + width / 2, (posY + height / 2) - 250);
				carryArm->SetScale(2, 2);
				carryArm->SetBound(width, height);
				AddEntity(carryArm);
				break;*/

				/*Life * life = new Life();
				life->Initialize();
				life->SetPosition(posX + width / 2, posY + height / 2);
				life->SetScale(2, 2);
				life->SetBound(width, height);
				AddEntity(life);
				break;*/

				Helit * helit = new Helit(player);
				helit->Initialize();
				helit->SetPosition(posX + width / 2, (posY + height / 2) - 250);
				helit->SetScale(2, 2);
				helit->SetBound(40 * 2, 40 * 2);
				AddEntity(helit);
				break;

				/*Conveyor *conveyor = new Conveyor(EntityId::HeadBlueConveyor_ID);
				conveyor->Initialize(true);
				conveyor->SetPosition(posX + width / 2, posY + height / 2);
				conveyor->SetScale(2, 2);
				AddEntity(conveyor);
				break;*/

				/*Byte *byte = new Byte(player);
				byte->Initialize();
				byte->SetPosition(posX + width / 2, (posY + height / 2) - 30);
				byte->SetScale(2, 2);
				byte->SetBound(54 * 2, 74 * 2);
				AddEntity(byte);
				break;*/
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
	}
}

QuadTree * EntityManager::GetQuadTree()
{
	return quadTree;
}