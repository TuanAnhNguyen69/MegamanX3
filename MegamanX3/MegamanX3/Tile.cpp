#include "pch.h"
#include "Tile.h"

Tile::Tile(void)
{
	tileId = -1;
	posX = 0;
	posY = 0;
}

Tile::Tile(int id, int x, int y)
{
	tileId = id;
	posX = x;
	posY = y;
}

Tile::~Tile(void)
{
}
