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
	int index = GetIndex(entity->GetBound());

	if (nodes != nullptr) {
		if (index != -1) {
			nodes[index]->Insert(entity);
			return;
		}
	}

	if (index == -1) {
		this->entities.push_back(entity);
	}
	else {
		if (nodes == nullptr) {
			Split();
		}
		nodes[index]->Insert(entity);
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
	int index = this->GetIndex(entity->GetBound());
	if (index != -1) {
		for (auto child : entities) {
			returnEntities.push_back(child);
		}

		if (nodes != nullptr) {
			nodes[index]->GetEntitiesCollideAble(returnEntities, entity);
		}
	}
	else {
		GetAllEntities(returnEntities);
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

int QuadTree::GetIndex(RECT body)
{
	float middleVertical = bound.left + (bound.right - bound.left) / 2.0f;
	float middleHorizontal = bound.top + (bound.bottom - bound.top) / 2.0f;
	
	if (body.top > bound.top && body.bottom < middleHorizontal) {
		if (body.left > bound.left && body.right < middleVertical) {
			return 0;
		}
		else if (body.left > middleVertical && body.right < bound.right) {
			return 1;
		}
	}
	else if (body.top > middleHorizontal && body.bottom < bound.bottom) {
		if (body.left > bound.left && body.right < middleVertical) {
			return 2;
		}
		else if (body.left > middleVertical && body.right < bound.right) {
			return 3;
		}
	}
	return -1;
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
