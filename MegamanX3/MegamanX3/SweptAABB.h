#pragma once
#include <cmath>
#include <algorithm>
#include <limits>

enum CollideDirection{TOP, BOT, LEFT, RIGHT, NONE};

struct Box
{
	// position of top-left corner
	float x, y;

	// dimensions
	float width, height;

	// velocity
	float vx, vy;
};

Box GetSweptBroadphaseBox(Box b)
{
	Box broadphasebox;
	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphasebox.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphasebox.width = b.vx > 0 ? b.vx + b.width : b.width - b.vx;
	broadphasebox.height = b.vy > 0 ? b.vy + b.height : b.height - b.vy;

	return broadphasebox;
}

bool AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.width < b2.x || b1.x > b2.x + b2.width || b1.y + b1.height < b2.y || b1.y > b2.y + b2.height);
}

float SweptAABB(Box b1, Box b2,CollideDirection& collideDirection) {
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.width);
		xInvExit = (b2.x + b2.width) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.width) - b1.x;
		xInvExit = b2.x - (b1.x + b1.width);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.height);
		yInvExit = (b2.y + b2.height) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.height) - b1.y;
		yInvExit = b2.y - (b1.y + b1.height);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		collideDirection = NONE;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				collideDirection = LEFT;
			}
			else
			{
				collideDirection = RIGHT;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				collideDirection = BOT;
			}
			else
			{
				collideDirection = TOP;
			}
		}

		// return the time of collision
		return entryTime;
	}
}