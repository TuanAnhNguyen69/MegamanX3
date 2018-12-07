#ifndef _MAP_H
#define _MAP_H

#include "QuadTree.h"
#include "Sprite.h"
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>

class Map
{
public:
	Map();
	~Map();

	void Initialize(LPCTSTR filePath);
	void Update();
	void Render();

	int GetWidth();
	int GetHeight();

	int GetTileWidth();
	int GetTileHeight();

	QuadTree *GetQuadTree();

private:
	QuadTree *quadTree;
	LPCTSTR GetTextureName(EntityId entityId);
};

#endif