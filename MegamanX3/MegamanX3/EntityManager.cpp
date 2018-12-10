#include "pch.h"
#include "EntityManager.h"

EntityManager *EntityManager::instance = nullptr;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
	RemoveAllEntities();
}

void EntityManager::Update()
{
	int size = entities.size();
	for (int index = 0; index < size; index++) {
		if (camera) {
			entities[index]->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
				SCREEN_HEIGHT / 2 - camera->GetCenter().y);
		}
		entities[index]->Update();
	}
}

void EntityManager::Render()
{
	int size = entities.size();
	for (int index = 0; index < size; index++) {
		entities[index]->Render();
	}
}

Entity * EntityManager::AddEntity(EntityId entityId)
{
	Entity *entity = new Entity(entityId);
	entities.push_back(entity);
	return entity;
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

void EntityManager::Initialize(Camera * camera)
{
	this->camera = camera;
}

std::vector<Entity*> EntityManager::GetAllEntities()
{
	return entities;
}
