#include "pch.h"
#include "Engine.h"
#include "ResourceManager.h"

Engine *Engine::instance = nullptr;


Engine::Engine()
{
	graphics = nullptr;
}

Engine::~Engine()
{
	if (graphics) {
		delete graphics;
		graphics = nullptr;
	}

	if (spriteHandler) {
		spriteHandler->Release();
		spriteHandler = nullptr;
	}
}

bool Engine::InitializeGraphics(HWND hwnd)
{
	graphics = new Graphics();
	graphics->SetHwnd(hwnd);
	return graphics->InitializeDX();
}

bool Engine::Initialize(HINSTANCE instance, HWND hwnd)
{
	graphics->Initialize();
	HRESULT result = D3DXCreateSprite(graphics->GetDevice(), &spriteHandler);
	if (FAILED(result)) {
		return false;
	}
	ResourceManager::GetInstance()->LoadTextureResource(graphics->GetDevice(), "mario-shell-sprite.png");
	animatedSprite = new AnimatedSprite(15, 1.0, true);
	animatedSprite->Initialize(graphics->GetDevice(), "mario-shell-sprite", 3.0f, 3.0f, 85.0f, 64.0f);
	
	sprite = new Sprite(80, 64);
	sprite->Initialize(graphics->GetDevice(), "mario-shell-sprite");
	return true;
}
 
void Engine::Run()
{
	Update();
	Render();
}

void Engine::Release()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

Graphics * Engine::GetGraphics()
{
	return graphics;
}

Engine * Engine::GetEngine()
{
	if (instance == nullptr) {
		instance = new Engine();
	}
	return instance;
}

LPD3DXSPRITE Engine::GetSpriteHandler()
{
	return spriteHandler;
}

void Engine::Update()
{
	animatedSprite->Update();
	sprite->Update();
}

void Engine::Render()
{
	graphics->BeginScene(D3DCOLOR_ARGB(1, 0, 0, 0));
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	animatedSprite->Render(D3DXVECTOR3(300, 300, 0));
	sprite->Render(D3DXVECTOR3(100, 100, 0));
	spriteHandler->End();
	graphics->EndScene();
}