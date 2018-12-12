#include "pch.h"
#include "GameScene.h"
#include "Collision.h"
#include <iostream>
#include <vector>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	if (player) {
		delete player;
		player = nullptr;
	}

	if (camera) {
		delete camera;
		camera = nullptr;
	}

	if (map) {
		delete map;
		map = nullptr;
	}
}

bool GameScene::Initialize()
{

	map = new Map();
	map->Initialize("aaaaa");

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetCenter(SCREEN_WIDTH / 2, 0);
	
	EntityManager::GetInstance()->Initialize(camera);

	player = new Player();
	player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), camera);
	player->SetPosition(SCREEN_WIDTH / 2, 200);

	debugDraw = new DebugDraw();
	return true;
}

void GameScene::DrawQuadtree(QuadTree *quadtree)
{
	if (quadtree->GetNodes())
	{
		for (size_t i = 0; i < 4; i++)
		{
			DrawQuadtree(quadtree->GetNodes()[i]);
		}
	}

	debugDraw->DrawRect(quadtree->GetBound());

	if (quadtree->GetNodes())
	{
		for (size_t i = 0; i < 4; i++)
		{
			debugDraw->DrawRect(quadtree->GetNodes()[i]->GetBound());
		}
	}
}

void GameScene::Update()
{
	CheckCollision();
	map->Update();
	player->Update();
	CheckCamera();
}

void GameScene::CheckCollision()
{
	std::vector<Entity *> listCollision;
	int widthBottom = 0;
	map->GetQuadTree()->GetEntitiesCollideAble(listCollision, player->GetEntity());
	
	for (size_t index = 0; index < listCollision.size(); index++) {
		RECT broadphase = Collision::GetSweptBroadphaseRect(player->GetEntity());
		if (Collision::IsCollide(broadphase, listCollision.at(index)->GetBound()))
		{
			Entity::CollisionReturn collideData;
			float collisionTime = Collision::SweptAABB(player->GetEntity(), listCollision.at(index), collideData);
			if (collisionTime < 1.0f) //collisiontime > 0 &&
			{
				Entity::SideCollisions sidePlayer = Collision::GetSideCollision(player->GetEntity(), collideData);
				Entity::SideCollisions sideImpactor = Collision::GetSideCollision(listCollision.at(index), collideData);

				player->OnCollision(listCollision.at(index), sidePlayer, collideData);
				listCollision.at(index)->OnCollision(player->GetEntity(), sideImpactor, collideData);

				if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
					|| sidePlayer == Entity::BottomRight) {
					int bot = collideData.RegionCollision.right - collideData.RegionCollision.left;
					if (bot > widthBottom) {
						widthBottom = bot;
					}
				}
			}
		}

			
			
	}

	//if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING) {
	//	player->OnNoCollisionWithBottom();
	//}
}

void GameScene::CheckCamera() {
	camera->SetCenter(player->GetPosition());
	if (camera->GetBound().left < 0)
	{
		camera->SetCenter(camera->GetWidth() / 2, camera->GetCenter().y);
	}

	if (camera->GetBound().right > map->GetWidth())
	{
		camera->SetCenter(map->GetWidth() - camera->GetWidth() / 2,
			camera->GetCenter().y);
	}

	if (camera->GetBound().top < 0)
	{
		camera->SetCenter(camera->GetCenter().x, camera->GetHeight() / 2);
	}

	if (camera->GetBound().bottom > map->GetHeight())
	{
		camera->SetCenter(camera->GetCenter().x,
			map->GetHeight() - camera->GetHeight() / 2);
	}
}

void GameScene::Render()
{
	auto list = EntityManager::GetInstance()->GetAllEntities();
	for (int index = 0; index < list.size(); index++) {
		debugDraw->DrawRect(list.at(index)->GetBound(), camera);
	}
	map->RenderBackground(camera);
}
