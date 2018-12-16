#ifndef _MAP_H
#define _MAP_H

#include "QuadTree.h"
#include "Sprite.h"
#include <map>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include "Tile.h"
#include "Camera.h"

class Map
{
public:
	Map();
	~Map();

	void Initialize(LPCTSTR filePath);
	void Update();
	void RenderBackground(Camera *camera);
	int GetWidth();
	int GetHeight();

	int GetTileWidth();
	int GetTileHeight();

	QuadTree *GetQuadTree();

private:
	Sprite * backgroundSprite;
	std::map<int, Tile*> *tiles; // tất cả tiles từ file
	QuadTree *quadTree;
	void LoadQuadtree(LPCTSTR filePath);
	void LoadBackground(LPCTSTR filePath);
	std::list<int> *GetAvailableTiles(RECT viewport);
	int tilesColCount;
	int tilesRowCount;
};

#endif