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
		if (Collision::IsCollide(collidableEntity[index]->GetBound(), camera->GetBound()))
		{
			if (camera) {
				collidableEntity[index]->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
					SCREEN_HEIGHT / 2 - camera->GetCenter().y);
			}

			if (collidableEntity[index]->entityId == Canon_ID) {
				int a = 0;
			}

			collidableEntity[index]->Update();
		}
		else {
			if (collidableEntity[index]->GetEntityId() == EntityId::MegamanBullet_ID
				|| collidableEntity[index]->GetEntityId() == EntityId::GunnerRocket_ID
				|| collidableEntity[index]->GetEntityId() == EntityId::HeliRocket_ID
				|| collidableEntity[index]->GetEntityId() == EntityId::Canon_ID) {
				RemoveEntity(collidableEntity[index]);
			}
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
	int playerCollidableEntitySize = playerCollidableEntity.size();
	for (size_t index = 0; index < playerCollidableEntitySize; index++) {
		if (Collision::IsCollide(playerCollidableEntity.at(index)->GetBound(), camera->GetBound())) {
			std::vector<Entity*> collidableEntity;
			if (playerCollidableEntity.at(index)->GetEntityId() == EntityId::BlastHornet_ID) {
				int a = 0;
			}
			quadTree->GetEntitiesCollideAble(collidableEntity, playerCollidableEntity.at(index)->GetBound());
			int collidableEntitySize = collidableEntity.size();
			for (size_t otherIndex = 0; otherIndex < collidableEntitySize; otherIndex++) {
				if (Collision::IsCollide(collidableEntity.at(otherIndex)->GetBound(), camera->GetBound())) {
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

							collidableEntity.at(otherIndex)->OnCollision(playerCollidableEntity.at(index), impactorSide, collideData);
							playerCollidableEntity.at(index)->OnCollision(collidableEntity.at(otherIndex), entitySide, collideData);
						}
					}
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
		std::cout << "numOBJ" << count << std::endl;
		for (int i = 0; i < count; i++)
		{
			if (i == 167) {
				int a = 0;
			}

			float enumValue;
			int id;
			objects >> id >> posX >> posY >> width >> height;
			EntityId entityId = (EntityId)id;
			switch (entityId)
			{
			case EntityId::Shurikein_ID:
			{
				Shuriken *shuriken = new Shuriken(player);
				shuriken->SetPosition(posX + width / 2 + 20, (posY + height / 2));
				shuriken->Initialize();
				AddEntity(shuriken);
				break;

			}

			case EntityId::Byte_ID:
			{
				Byte *byte = new Byte(player);
				byte->Initialize();
				byte->SetPosition(posX + width / 2, (posY + height / 2));
				byte->SetScale(2, 2);
				byte->SetBound(54, 74);
				AddEntity(byte);
				break;
			}

			case EntityId::BlastHornet_ID:
			{
				BlastHornet *boss = new BlastHornet(player);
				boss->SetPosition(posX + width / 2, (posY + height / 2));
				boss->SetScale(1.5, 1.5);
				boss->SetBound(30, 40);
				boss->Initialize();
				AddEntity(boss);
				break;
			}

			case EntityId::CheckPoint_ID:
			{
				Entity * checkPoint = new Entity(CheckPoint_ID);
				checkPoint->SetPosition(posX + width / 2, (posY + height / 2));
				checkPoint->SetBound(width, height);
				AddEntity(checkPoint);
				break;
			}

			case EntityId::Helit_ID:
			{
				Helit * helit = new Helit(player);
				helit->Initialize();
				helit->SetPosition(posX + width / 2, (posY + height / 2));
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

			case EntityId::RightFaceHeadGunner_ID:
			{
				HeadGunner * headGunner = new HeadGunner(this->player, EntityId::RightFaceHeadGunner_ID);
				headGunner->Initialize(true);
				headGunner->SetPosition(posX + width / 2, posY + height / 2);
				headGunner->SetScale(2, 2);
				headGunner->SetBound(width, height);
				AddEntity(headGunner);
				break;
			}

			case EntityId::LeftFaceHeadGunner_ID:
			{
				HeadGunner * headGunner = new HeadGunner(this->player, EntityId::LeftFaceHeadGunner_ID);
				headGunner->Initialize(true);
				headGunner->SetPosition(posX + width / 2, posY + height / 2);
				headGunner->SetScale(2, 2);
				headGunner->SetBound(width, height);
				AddEntity(headGunner);
				break;
			}												

			case EntityId::Door_ID:
			{
				Door * door = new Door();
				door->Initialize();
				door->SetPosition(posX + width / 2, posY + height / 2);
				door->SetBound(width, height);
				AddEntity(door);
				break;
			}

			case EntityId::Thorn_ID:
			{
				break;
			}

			case EntityId::DoubleBox_ID:
			{
				break;
			}
				
			case EntityId::QuadraBox_ID:
			{
				break;
			}

			case EntityId::VerticalBombBox_ID:
			{
				break;
			}

			case EntityId::HorizontalBombBox_ID:
			{
				break;
			}
	
			case EntityId::Roof_ID:
			{
				Roof * roof = new Roof();
				roof->SetPosition(posX + width / 2, posY + height / 2);
				roof->SetBound(width, height);
				roof->Initialize();
				AddEntity(roof);
				break;
			}
			
			case EntityId::SmallEnergy_ID: 
			{
				break;
			}
			
			case EntityId::BigEnergy_ID:
			{
				Life * life = new Life();
				life->Initialize();
				life->SetPosition(posX + width / 2, posY + height / 2);
				life->SetScale(2, 2);
				life->SetBound(width, height);
				AddEntity(life);
				break;
			}

			case EntityId::ChimeraArmor_ID:
			{
				break;
			}

			case EntityId::Cargo_ID:
			{
				CargoShip *cargo = new CargoShip(player);
				cargo->SetPosition((posX + width / 2) - 150, (posY + height / 2));
				cargo->SetScale(2, 2);
				cargo->SetBound(256, 88);
				cargo->Initialize();
				AddEntity(cargo);
				break;
			}

			case EntityId::BigElevator_ID:
			{
				Elevator * elevator = new Elevator();
				elevator->SetPosition(posX + width / 2, posY + height / 2);
				elevator->SetBound(width, height * 0.6);
				elevator->SetScale(2, 2);
				elevator->Initialize();
				AddEntity(elevator);
				break;
			}
			case EntityId::UpPlatform_ID:
			{
				UpPlatform * upPlatform = new UpPlatform();
				upPlatform->SetPosition(posX + width / 2, posY + height / 2);
				upPlatform->SetBound(width, height);
				upPlatform->Initialize();
				AddEntity(upPlatform);
				break;
			}
			case EntityId::DownPlatform_ID:
			{
				DownPlatform * downPlatform = new DownPlatform();
				downPlatform->SetPosition(posX + width / 2, posY + height / 2);
				downPlatform->SetBound(width, height);
				downPlatform->Initialize();
				AddEntity(downPlatform);
				break;
			}
			case EntityId::Platform_ID:
			{
				Platform * platform = new Platform();
				platform->SetPosition(posX + width / 2, posY + height / 2);
				platform->SetBound(width, height);
				platform->Initialize();
				AddEntity(platform);
				break;
			}

			case EntityId::HallHole_ID:
			{
				Entity * hallHole = new Entity(CheckPoint_ID);
				hallHole->SetPosition(posX + width / 2, (posY + height / 2));
				hallHole->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "hall_hole", width, height);
				hallHole->SetBound(width, height);
				AddEntity(hallHole);
				break;
			}

			case EntityId::WallHoleLeft_ID:
			{
				Entity * wallHoleLeft = new Entity(CheckPoint_ID);
				wallHoleLeft->SetPosition(posX + width / 2, (posY + height / 2));
				wallHoleLeft->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "wall_hole_left", width, height);
				wallHoleLeft->SetBound(width, height);
				AddEntity(wallHoleLeft);
				break;
			}

			case EntityId::WallHoleRight_ID:
			{
				Entity * wallHoleRight = new Entity(CheckPoint_ID);
				wallHoleRight->SetPosition(posX + width / 2, (posY + height / 2));
				wallHoleRight->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), "wall_hole_right", width, height);
				wallHoleRight->SetBound(width, height);
				AddEntity(wallHoleRight);
				break;
			}

			case EntityId::LeftBlueConveyor_ID:
			case EntityId::RightBlueConveyor_ID:
			case EntityId::LeftYellowConveyor_ID:
			case EntityId::RightYellowConveyor_ID:
			case EntityId::LeftSmallConveyor_ID:
			case EntityId::RightSmallConveyor_ID:
			{
				Conveyor *conveyor = new Conveyor(entityId);
				conveyor->Initialize();
				conveyor->SetPosition(posX + width / 2, posY + height / 2);
				conveyor->SetBound(width, height);
				AddEntity(conveyor);
				break;
			}
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