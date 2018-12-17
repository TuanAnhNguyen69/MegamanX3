#ifndef _ENTITY_MANAGER_H
#define _ENTITY_MANAGER_H

#include "Entity.h"
#include "Camera.h"
#include "SystemDefs.h"
#include "QuadTree.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include"Player.h"

class Player;

class EntityManager
{
public:

	~EntityManager();

	void Update();
	void Render();

	int AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
	void RemoveAllEntities();

	bool ContainsEntity(Entity *entity);
	bool ContainsEntity(Entity *entity, int &index);
	std::vector<Entity*> GetAllEntities();

	static EntityManager *GetInstance();
	QuadTree *GetQuadTree();
	void Initialize(Player *player, Camera *camera, LPCTSTR fileName, int mapWidth, int mapHeight);

private:
	std::vector<Entity*> entities;
	EntityManager();
	static EntityManager *instance;
	Camera *camera;
	QuadTree *quadTree;
	void LoadQuadtree(LPCTSTR filePath);
	Player * player;
};

#endif
