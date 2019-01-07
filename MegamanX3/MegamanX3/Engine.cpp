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
	resourceManager->LoadTextureResource(graphics->GetDevice(), "stage.png");
	resourceManager->LoadTextureResource(graphics->GetDevice(), "PlayerPaper.png");
	resourceManager->LoadTextureResource(graphics->GetDevice(), "platform.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "head_gunner_rocket.png",D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "x.png", D3DCOLOR_XRGB(50, 96, 166));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "life.png", D3DCOLOR_XRGB(50, 96, 166));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "door.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "head_gunner.png", D3DCOLOR_XRGB(50, 96, 166));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "notor_banger.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "canon.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "helit.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "carry_arm.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "helit_rocket.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "byte.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "byte_bomb.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "charging.png", D3DCOLOR_XRGB(237, 28, 36));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "normal_bullet.png", D3DCOLOR_XRGB(50, 96, 166));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "super_bullet.png", D3DCOLOR_XRGB(50, 96, 166));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "extreme_bullet.png", D3DCOLOR_XRGB(50, 96, 166));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "elevator.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "left_yellow_conveyor.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "right_yellow_conveyor.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "left_blue_conveyor.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "right_blue_conveyor.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "small_conveyor.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "box.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "thorn.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "blast_hornet.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "blast_hornet_die.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "bee.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "die.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "shuriken.png", D3DCOLOR_XRGB(255, 255, 255));

	resourceManager->LoadTextureResource(graphics->GetDevice(), "box2.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "box3.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "box4.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "box_vertical.png", D3DCOLOR_XRGB(255, 255, 255));
	resourceManager->LoadTextureResource(graphics->GetDevice(), "box_horizontal.png", D3DCOLOR_XRGB(255, 255, 255));

	//D3DCOLOR_XRGB(50, 96, 166)

	input = new Input();
	input->Initialize(instance, hwnd);

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
	//entityManager->Update();
	//entityManager->CheckCollide();
	input->Update();
}

void Engine::Render()
{
	graphics->BeginScene(D3DCOLOR_ARGB(1, 0, 0, 0));
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
	if (gameComponent != nullptr) {
		gameComponent->Render();
	}
	//entityManager->Render();

	spriteHandler->End();
	graphics->EndScene();
}