#ifndef _ENGINE_H
#define _ENGINE_H

#include "Graphics.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Input.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "GameComponent.h"
#include "Camera.h"

class Engine
{
public:
	~Engine();

	bool InitializeGraphics(HWND hwnd);
	bool Initialize(HINSTANCE instance, HWND hwnd);
	void Run();
	void Release();

	void SetGameComponent(GameComponent *gameComponent);
	Input *GetInput();
	Camera *GetCamera();
	Graphics * GetGraphics();
	static Engine* GetEngine();
	LPD3DXSPRITE GetSpriteHandler();

private:
	Engine();
	void Update();
	void Render();

	Camera *camera;
	GameComponent *gameComponent;
	Input *input;
	ResourceManager *resourceManager;
	EntityManager *entityManager;
	Graphics *graphics;
	LPD3DXSPRITE spriteHandler;

	static Engine *instance;
};

#endif