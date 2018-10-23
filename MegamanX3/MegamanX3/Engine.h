#ifndef _ENGINE_H
#define _ENGINE_H

#include "Graphics.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

class Engine
{
public:
	~Engine();

	bool InitializeGraphics(HWND hwnd);
	bool Initialize(HINSTANCE instance, HWND hwnd);
	void Run();
	void Release();

	Graphics * GetGraphics();
	static Engine* GetEngine();
	LPD3DXSPRITE GetSpriteHandler();

private:
	Engine();
	void Update();
	void Render();

	Sprite *sprite;
	AnimatedSprite *animatedSprite;
	LPD3DXSPRITE spriteHandler;
	Graphics *graphics;
	static Engine *instance;
};

#endif