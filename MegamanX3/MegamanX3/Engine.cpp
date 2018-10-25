#include "pch.h"
#include "Engine.h"
#include "ResourceManager.h"
#include <iostream>

Engine *Engine::instance = nullptr;


Engine::Engine()
{
	graphics = nullptr;
	entityManager = nullptr;
	resourceManager = nullptr;
	input = nullptr;
	gameComponent = nullptr;
	spriteHandler = nullptr;
	camera = nullptr;
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

	if (input) {
		delete input;
		input = nullptr;
	}

	if (resourceManager) {
		delete resourceManager;
		resourceManager = nullptr;
	}

	if (entityManager) {
		delete entityManager;
		entityManager = nullptr;
	}
	
	if (gameComponent) {
		delete gameComponent;
		gameComponent = nullptr;
	}

	if (camera) {
		delete camera;
		camera = nullptr;
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
	entityManager = EntityManager::GetInstance();

	resourceManager = ResourceManager::GetInstance();
	resourceManager->LoadTextureResource(graphics->GetDevice(), "mario-shell-sprite.png");
	resourceManager->LoadTextureResource(graphics->GetDevice(), "stage.png");

	input = new Input();
	input->Initialize(instance, hwnd);

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetCenter(0, 0);

	graphics->Initialize();

	HRESULT result = D3DXCreateSprite(graphics->GetDevice(), &spriteHandler);
	if (FAILED(result)) {
		return false;
	}
	
	if (gameComponent != nullptr) {
		if (!gameComponent->Initialize()) {
			return false;
		}
	}
	else {
		std::cout << "NO GAME COMPONENT" << std::endl;
	}
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

void Engine::SetGameComponent(GameComponent * gameComponent)
{
	this->gameComponent = gameComponent;
}

Input * Engine::GetInput()
{
	return input;
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
	if (gameComponent != nullptr) {
		gameComponent->Update();
	}
	entityManager->Update();
	input->Update();
}

void Engine::Render()
{
	graphics->BeginScene(D3DCOLOR_ARGB(1, 0, 0, 0));
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
	if (gameComponent != nullptr) {
		gameComponent->Render();
	}
	entityManager->Render();

	spriteHandler->End();
	graphics->EndScene();
}