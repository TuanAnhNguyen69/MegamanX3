#include "pch.h"
#include "QuadTree.h"

QuadTree::QuadTree(int level, RECT bound)
{
	this->level = level;
	this->bound = bound;
}

QuadTree::~QuadTree()
{
}

void QuadTree::Clear()
{
	if (nodes) {
		for (int index = 0; index < 4; index++) {
			if (nodes[index]) {
				nodes[index]->Clear();
				delete nodes[index];
				nodes[index] = nullptr;
			}
		}
		delete[] nodes;
	}
	entityIndexs.clear();
}

void QuadTree::Insert(int index, Entity * entity)
{
	if (nodes) {
		if (nodes[0]->IsContain(entity->GetBound())) {
			nodes[0]->Insert(index, entity);
		}
		if (nodes[1]->IsContain(entity->GetBound())) {
			nodes[1]->Insert(index, entity);
		}
		if (nodes[2]->IsContain(entity->GetBound())) {
			nodes[2]->Insert(index, entity);
		}
		if (nodes[3]->IsContain(entity->GetBound())) {
			nodes[3]->Insert(index, entity);
		}
		return;
	}

	if (this->IsContain(entity->GetBound())) {
		entityIndexs.push_back(index);
	}

	if (entityIndexs.size() > MAX_OBJECT_IN_REGION && level < MAX_LEVEL) {
		Split();
		while (!entityIndexs.empty()) {
			if (nodes[0]->IsContain()) {
				nodes[0]->Insert(entities.back());
			}
			if (nodes[1]->IsContain(entities.back())) {
				nodes[1]->Insert(entities.back());
			}
			if (nodes[2]->IsContain(entities.back())) {
				nodes[2]->Insert(entities.back());
			}
			if (nodes[3]->IsContain(entities.back())) {
				nodes[3]->Insert(entities.back());
			}
			entities.pop_back();
		}
	}
}

void QuadTree::GetInBoundEntities(std::vector<int>& returnEntities, RECT bound)
{
	if (nodes) {
		if (nodes[0]->IsContain(bound)) {
			nodes[0]->GetInBoundEntities(returnEntities, bound);
		}
		if (nodes[1]->IsContain(bound)) {
			nodes[1]->GetInBoundEntities(returnEntities, bound);
		}
		if (nodes[2]->IsContain(bound)) {
			nodes[2]->GetInBoundEntities(returnEntities, bound);
		}
		if (nodes[3]->IsContain(bound)) {
			nodes[3]->GetInBoundEntities(returnEntities, bound);
		}
		return;
	}

	if (this->IsContain(bound)) {
		for (auto index : entityIndexs) {
				returnEntities.push_back(index);
		}
	}
}

RECT QuadTree::GetBound()
{
	return bound;
}

QuadTree ** QuadTree::GetNodes()
{
	return nodes;
}

void QuadTree::Split()
{
	nodes = new QuadTree * [4];
	RECT rect;

	int width = (bound.right - bound.left) / 2;
	int height = (bound.bottom - bound.top) / 2;
	
	rect.left = bound.left;
	rect.right = rect.left + width;
	rect.top = bound.top;
	rect.bottom = rect.top + height;
	nodes[0] = new QuadTree(level + 1, bound);

	rect.left = bound.left + width;
	rect.right = rect.left + width;
	rect.top = bound.top;
	rect.bottom = rect.top + height;
	nodes[1] = new QuadTree(level + 1, bound);

	rect.left = bound.left;
	rect.right = rect.left + width;
	rect.top = bound.top + height;
	rect.bottom = rect.top + height;
	nodes[2] = new QuadTree(level + 1, bound);

	rect.left = bound.left + width;
	rect.right = rect.left + width;
	rect.top = bound.top + height;
	rect.bottom = rect.top + height;
	nodes[3] = new QuadTree(level + 1, bound);
}

bool QuadTree::IsContain(RECT rect)
{
	if (rect.left >= bound.left && rect.right <= bound.right
		&& rect.top >= bound.top && rect.bottom <= bound.bottom) {
		return true;
	}
	return false;
}
