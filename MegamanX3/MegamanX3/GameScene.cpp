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

	map = new Background();
	map->Initialize("aaaaa", 2);

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetCenter(SCREEN_WIDTH / 2, 0);

	player = new Player();
	player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), camera);
	player->SetPosition(1115, 1630);

	EntityManager::GetInstance()->Initialize(player, camera, "aaaaa", map->GetWidth(), map->GetHeight());

	
	debugDraw = new DebugDraw();
	debugDraw->SetColor(D3DCOLOR_XRGB(50, 96, 55));
	debugDraw->SetLineSize(5);
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
	EntityManager::GetInstance()->CheckCollide();
	CheckCamera();
	player->Update();
	EntityManager::GetInstance()->Update();
}

void GameScene::CheckCollision()
{
	int widthBottom = 0;
	std::vector<Entity*> collidableEntity;
	EntityManager::GetInstance()->GetQuadTree()->GetEntitiesCollideAble(collidableEntity, camera->GetBound());
	for (size_t index = 0; index < collidableEntity.size(); index++) {
		RECT broadphase = Collision::GetSweptBroadphaseRect(player);
		if (Collision::IsCollide(broadphase, collidableEntity.at(index)->GetBound()))
		{
			if (collidableEntity.at(index)->GetEntityId() == EntityId::Canon_ID) {
				int a = 0;
			}
			Entity::CollisionReturn collideData;
			float collisionTime = Collision::SweptAABB(player, collidableEntity.at(index), collideData);
			if (collisionTime < 1.0f) //collisiontime > 0 &&
			{
				Entity::CollisionSide sidePlayer = Collision::GetSideCollision(player, collideData);
				Entity::CollisionSide sideImpactor = Collision::GetSideCollision(collidableEntity.at(index), collideData);

				player->OnCollision( collidableEntity.at(index), sidePlayer, collideData);
				collidableEntity.at(index)->OnCollision(player, sideImpactor, collideData);

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

	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING) {
		player->OnNoCollisionWithBottom();
	}
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
	map->RenderBackground(camera);
	player->Render();
	auto list = EntityManager::GetInstance()->GetAllEntities();
	for (int index = 0; index < list.size(); index++) {
		debugDraw->DrawRect(list.at(index)->GetBound(), camera);
	}
	EntityManager::GetInstance()->Render();
	DrawQuadtree(EntityManager::GetInstance()->GetQuadTree());
}
