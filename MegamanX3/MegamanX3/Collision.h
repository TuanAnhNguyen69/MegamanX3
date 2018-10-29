#ifndef _COLLISION_H
#define _COLLISION_H

#include <d3dx9.h>
#include <d3d9.h>
#include "Entity.h"

class Collision
{
public:
	Collision();
	~Collision();

	static Entity::CollisionReturn RectAndRect(RECT rect, RECT rect2);
	static Entity::SideCollisions GetSideCollision(Entity *e1, Entity *e2);
	static Entity::SideCollisions GetSideCollision(Entity *e1, Entity::CollisionReturn data);
	static bool RectangleAndCircle(RECT rect, int circlex, int circley, int circleRadius);
	static bool PointAndRectangle(float x, float y, RECT rect);

private:
	static bool IsCollide(RECT rect1, RECT rect2);
};

#endif