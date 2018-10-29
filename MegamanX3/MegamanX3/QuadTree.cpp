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
	entities.clear();
}

void QuadTree::Insert(Entity * entity)
{
	if (nodes) {
		if (nodes[0]->IsContain(entity)) {
			nodes[0]->Insert(entity);
		}
		if (nodes[1]->IsContain(entity)) {
			nodes[1]->Insert(entity);
		}
		if (nodes[2]->IsContain(entity)) {
			nodes[2]->Insert(entity);
		}
		if (nodes[3]->IsContain(entity)) {
			nodes[3]->Insert(entity);
		}
		return;
	}

	if (this->IsContain(entity)) {
		entities.push_back(entity);
	}

	if (entities.size() > MAX_OBJECT_IN_REGION && level < MAX_LEVEL) {
		Split();
		while (!entities.empty()) {
			if (nodes[0]->IsContain(entities.back())) {
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

void QuadTree::GetAllEntities(std::vector<Entity*>& returnEntities)
{
	for (auto child : entities) {
		returnEntities.push_back(child);
	}
	if (nodes) {
		for (int index = 0; index < 4; index++) {
			nodes[index]->GetAllEntities(returnEntities);
		}
	}
}

void QuadTree::GetEntitiesCollideAble(std::vector<Entity*>& returnEntities, Entity * entity)
{
	if (nodes) {
		if (nodes[0]->IsContain(entity)) {
			nodes[0]->GetEntitiesCollideAble(returnEntities, entity);
		}
		if (nodes[1]->IsContain(entity)) {
			nodes[1]->GetEntitiesCollideAble(returnEntities, entity);
		}
		if (nodes[2]->IsContain(entity)) {
			nodes[2]->GetEntitiesCollideAble(returnEntities, entity);
		}
		if (nodes[3]->IsContain(entity)) {
			nodes[3]->GetEntitiesCollideAble(returnEntities, entity);
		}
		return;
	}

	if (this->IsContain(entity)) {
		for (auto child : entities) {
			if (entity != child) {
				returnEntities.push_back(child);
			}
		}
	}
}

int QuadTree::GetTotalEntities()
{
	int total = entities.size();
	if (nodes) {
		for (int index = 0; index < 4; index++) {
			total += nodes[index]->GetTotalEntities();
		}
	}
	return total;
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

bool QuadTree::IsContain(Entity * entity)
{
	RECT rect = entity->GetBound();
	if (rect.left >= bound.left && rect.right <= bound.right
		&& rect.top >= bound.top && rect.bottom <= bound.bottom) {
		return true;
	}
	return false;
}
