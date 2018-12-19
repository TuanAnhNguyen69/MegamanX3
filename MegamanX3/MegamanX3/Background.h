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

class Background
{
public:
	Background();
	~Background();

	void Initialize(LPCTSTR filePath, int scaleFactor);
	void Update();
	void RenderBackground(Camera *camera);
	int GetWidth();
	int GetHeight();

	void SetScale(int x, int y);
	D3DXVECTOR2 GetScale(int x, int y);
private:
	Sprite * backgroundSprite;
	std::map<int, Tile*> *tiles; // tất cả tiles từ file
	QuadTree *quadTree;
	void LoadBackground(LPCTSTR filePath);
	std::list<int> *GetAvailableTiles(RECT viewport);
	D3DXVECTOR2 scale;
};

#endif