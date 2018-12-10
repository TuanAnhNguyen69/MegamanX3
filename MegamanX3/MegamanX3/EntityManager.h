#ifndef _ENTITY_MANAGER_H
#define _ENTITY_MANAGER_H

#include "Entity.h"
#include "Camera.h"
#include "SystemDefs.h"
#include <vector>

class EntityManager
{
public:
	
	~EntityManager();

	void Update();
	void Render();
		
	Entity *AddEntity(EntityId entityId);
	void RemoveEntity(Entity *entity);
	void RemoveAllEntities();

	bool ContainsEntity(Entity *entity);
	bool ContainsEntity(Entity *entity, int &index);
	std::vector<Entity*> GetAllEntities();

	static EntityManager *GetInstance();
	void Initialize(Camera *camera);

private:
	std::vector<Entity*> entities;
	EntityManager();
	static EntityManager *instance;
	Camera *camera;
};

#endif
