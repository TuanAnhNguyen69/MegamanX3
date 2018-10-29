#ifndef _ENTITY_MANAGER_H
#define _ENTITY_MANAGER_H

#include "Entity.h"
#include <vector>

class EntityManager
{
public:
	
	~EntityManager();

	void Update();
	void Render();
		
	Entity *AddEntity();
	void RemoveEntity(Entity *entity);
	void RemoveAllEntities();

	bool ContainsEntity(Entity *entity);
	bool ContainsEntity(Entity *entity, int &index);
	std::vector<Entity*> GetAllEntities();

	static EntityManager *GetInstance();

private:
	std::vector<Entity*> entities;
	EntityManager();
	static EntityManager *instance;
};

#endif
