#include "pch.h"
#include "QuadTree.h"
#include <set>

QuadTree::~QuadTree()
{
}

QuadTree::QuadTree(int level, RECT bound)
{
	//chia lam 4
	this->bound = bound;
	this->level = level;
}

void QuadTree::Clear()
{
	if (nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (nodes[i])
			{
				nodes[i]->Clear();
				delete nodes[i];
				nodes[i] = nullptr;
			}
		}

		delete[] nodes;
	}
}

void QuadTree::Insert(Entity *entity)
{
	int index = GetNodeIndex(entity->GetBound());

	//neu node ta ton tai thi insert vao node con
	if (nodes != NULL)
	{
		if (index != -1)
		{
			nodes[index]->Insert(entity);
			return;
		}
	}

	//luc nay entity nam giua 2 Bound nen se add vao node nay luon
	if (index == -1)
	{
		this->entities.push_back(entity);
	}
	else
	{
		//node chua dc tao nen se tao va split roi moi insert
		if (nodes == NULL)
		{
			Split();
		}

		nodes[index]->Insert(entity);
	}
}

void QuadTree::Remove(Entity * entity)
{
	if (entity == nullptr) {
		return;
	}

	int nodeIndex = GetNodeIndex(entity->GetBound());

	if (nodeIndex == -1) {
		int size = entities.size();
		for (int index = 0; index < size; index++) {
			if (entities[index] == entity) {
				entities.erase(entities.begin() + index);
				break;
			}
		}
		return;
	}

	nodes[nodeIndex]->Remove(entity);
}

bool QuadTree::IsContain(Entity *entity)
{
	RECT r = entity->GetBound();

	if (r.left >= bound.left && r.right <= bound.right && r.top >= bound.top && r.bottom <= bound.bottom)
	{
		return true;
	}

	return false;
}

void QuadTree::Split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	nodes = new QuadTree *[4];

	RECT rect;

	int width = (bound.right - bound.left) / 2;
	int height = (bound.bottom - bound.top) / 2;

	//phan goc trai tren
	rect.left = bound.left;
	rect.right = rect.left + width;
	rect.top = bound.top;
	rect.bottom = rect.top + height;
	nodes[0] = new QuadTree(level + 1, rect);

	//phan goc phai tren
	rect.left = bound.left + width;
	rect.right = rect.left + width;
	rect.top = bound.top;
	rect.bottom = rect.top + height;
	nodes[1] = new QuadTree(level + 1, rect);

	//phan goc trai duoi
	rect.left = bound.left;
	rect.right = rect.left + width;
	rect.top = bound.top + height;
	rect.bottom = rect.top + height;
	nodes[2] = new QuadTree(level + 1, rect);

	//phan goc phai duoi
	rect.left = bound.left + width;
	rect.right = rect.left + width;
	rect.top = bound.top + height;
	rect.bottom = rect.top + height;
	nodes[3] = new QuadTree(level + 1, rect);
}

int QuadTree::GetTotalEntities()
{
	int total = entities.size();

	if (nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			total += nodes[i]->GetTotalEntities();
		}
	}

	return total;
}

QuadTree ** QuadTree::GetNodes()
{
	return nodes;
}

RECT QuadTree::GetBound()
{
	return bound;
}

int QuadTree::GetNodeIndex(RECT body)
{
	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/

	float middleVerticle = bound.left + (bound.right - bound.left) / 2.0f;
	float middleHorizontal = bound.top + (bound.bottom - bound.top) / 2.0f;

	if (body.top > bound.top && body.bottom < middleHorizontal)
	{
		//nam phia ben tren
		if (body.left > bound.left && body.right < middleVerticle)
		{
			//nam phia ben trai
			return 0;
		}
		else if (body.left > middleVerticle && body.right < bound.right)
		{
			//nam phia ben phai
			return 1;
		}
	}
	else if (body.top > middleHorizontal && body.bottom < bound.bottom)
	{
		//nam phia ben duoi
		if (body.left > bound.left && body.right < middleVerticle)
		{
			//nam phia ben trai
			return 2;
		}
		else if (body.left > middleVerticle && body.right < bound.right)
		{
			//nam phia ben phai
			return 3;
		}
	}

	return -1;
}

void QuadTree::GetAllEntities(std::vector<Entity*> &entitiesOut)
{
	for (auto child : entities)
	{
		entitiesOut.push_back(child);
	}

	if (nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			nodes[i]->GetAllEntities(entitiesOut);
		}
	}
}

void QuadTree::GetEntitiesCollideAble(std::vector<Entity*> &entitiesOut, Entity *entity)
{
	int index = this->GetNodeIndex(entity->GetBound());
	if (index == -1) {
		int a = 0;
	}
	if (index != -1)
	{
		//nhung Entity o day se la nam tren 2 node con nen chung ta cung se lay de set va cham
		for (auto child : entities)
		{
			/*bool exist = false;
			for (auto entity : entitiesOut) {
				if (child == entity) {
					exist = true;
					break;
				}
			}
			if (!exist) {*/
				entitiesOut.push_back(child);
			//}
		}

		if (nodes != NULL)
		{
			//kiem tra va lay cac node trong node con
			nodes[index]->GetEntitiesCollideAble(entitiesOut, entity);
		}
	}
	else
	{
		GetAllEntities(entitiesOut);
	}
}
