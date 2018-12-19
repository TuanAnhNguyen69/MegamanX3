#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include "Entity.h"
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#define MAX_LEVEL 5
#define MAX_OBJECT_IN_REGION 4

#pragma once

class QuadTree
{
public:

	QuadTree(int level, RECT bound);
	~QuadTree();
	void Clear();
	void Insert(Entity *entity);

	/*lay danh sach nhung Entity co kha nang xay ra va cham
	tra ve danh sach cac phan tu nam trong vung va cham */
	void GetEntitiesCollideAble(std::vector<Entity*> &entitiesOut, Entity *entity);

	void GetAllEntities(std::vector<Entity*> &entitiesOut);

	int GetTotalEntities();
	
	QuadTree **GetNodes();
	RECT GetBound();

protected:
	RECT bound;
	QuadTree **nodes;
	std::vector<Entity*> entities; //danh sach cac phan tu co trong vung va cham (Bound)

	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/
	int GetIndex(RECT body);

	void Split(); //thuc hien chia ra cac node

	bool IsContain(Entity *entity);
	int level; //tuong ung voi so node
};

#endif