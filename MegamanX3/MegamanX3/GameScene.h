#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "GameComponent.h"
#include "Player.h"

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
	Player *player;
};

#endif