#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include "Entity.h"
#include <vector>

#define MAX_LEVEL 5
#define MAX_OBJECT_IN_REGION 4

class QuadTree
{
public:
	QuadTree(int level, RECT bound);
	~QuadTree();

	void Clear();
	void Insert(Entity *entity);
	void GetAllEntities(std::vector<Entity*> &returnEntities);
	void GetEntitiesCollideAble(std::vector<Entity*> &returnEntities, Entity* entity);
	int GetTotalEntities();
private:
	int level;
	RECT bound;
	std::vector<Entity*> entities;
	QuadTree** nodes;

	int GetIndex(RECT body);
	void Split();
	bool IsContain(Entity *entity);
};

#endif