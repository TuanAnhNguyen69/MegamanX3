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
	void Insert(int index, Entity *entity);
	void GetInBoundEntities(std::vector<int> &returnEntities, RECT bound);
	RECT GetBound();
	QuadTree **GetNodes();

private:
	int level;
	RECT bound;
	std::vector<int> entityIndexs;
	QuadTree** nodes;

	void Split();
	bool IsContain(RECT bound);
	int id;
};

#endif