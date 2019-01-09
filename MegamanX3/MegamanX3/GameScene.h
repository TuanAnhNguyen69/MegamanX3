#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "GameComponent.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include "DebugDraw.h"
#include "Door.h"
#include "HealthX.h"

class GameScene :
	public GameComponent
{
public:
	GameScene();
	virtual ~GameScene();

	bool Initialize();
	void Update();
	void Render();

private:
	void CheckCollision();
	void DrawQuadtree(QuadTree *quadtree);
	void Revive();

	DebugDraw *debugDraw;
	Camera *camera;
	Background *map;
	Player *player;
	Enemy *currentBoss;
	Door * currentDoor;
	Entity * checkPoint;
	HealthBar *x_health;

	bool doorLock;
};

#endif