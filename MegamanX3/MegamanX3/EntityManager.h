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

	static EntityManager *GetInstance();

private:
	EntityManager();
	std::vector<Entity*> entities;
	static EntityManager *instance;
};

#endif
