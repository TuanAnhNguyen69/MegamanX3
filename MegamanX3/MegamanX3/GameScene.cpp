#include "pch.h"
#include "GameScene.h"
#include "Collision.h"
#include <iostream>
#include <vector>

const int PLAYER_AUTO_MOVE_DISTANCE = 176;
const int CAMERA_AUTO_MOVE_DISTANCE = 528;

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
	map->Initialize("blast_hornet_state", 4);
	//map->Initialize("testBoss", 2);
	

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->Initialize("blast_hornet_state");

	player = new Player();
	player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), camera);
	/*player->SetPosition(300, 1700);*/
	//player->SetPosition(6200, 1900);
	player->SetPosition(12051, 3860);
	camera->SetCenter(player->GetPosition());

	//EntityManager::GetInstance()->Initialize(player, camera, "testDoor", map->GetWidth(), map->GetHeight());
	EntityManager::GetInstance()->Initialize(player, camera, "blast_hornet_state", map->GetWidth(), map->GetHeight());	

	//Sound::getInstance()->loadSound((char*)"sound/BlastHornet.wav", "blasthornet");
	//Sound::getInstance()->play("blasthornet", false, 1);

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

void GameScene::Revive()
{
	player->SetPosition(checkPoint->GetPosition().x, checkPoint->GetPosition().y - 100);
}

void GameScene::Update()
{
	if (currentDoor && currentDoor->GetState() == Door::DoorState::OPENED) {
		if (!player->GetMovable()) {
			player->AutoMove();
			camera->AutoMove();
			if (player->GetAutoMovedDistance() >= PLAYER_AUTO_MOVE_DISTANCE) {
				player->SetMovable(true);
			}
		}

		if (camera->GetAutoMovedDistance() >= CAMERA_AUTO_MOVE_DISTANCE) {
			camera->StopAutoMove();
			currentDoor->SetState(Door::DoorState::CLOSING);
		}
	}
	
	CheckCollision();
	EntityManager::GetInstance()->CheckCollide();
	camera->Update(player->GetPosition());
	player->Update();
	EntityManager::GetInstance()->Update();
}

void GameScene::CheckCollision()
{
	int widthBottom = 0;
	std::vector<Entity*> collidableEntity;
	EntityManager::GetInstance()->GetQuadTree()->GetEntitiesCollideAble(collidableEntity, player->GetBound());
	int size = collidableEntity.size();
	for (size_t index = 0; index < size; index++) {
		if (Collision::IsCollide(collidableEntity.at(index)->GetBound(), camera->GetBound())) {
			RECT broadphase = Collision::GetSweptBroadphaseRect(player);
			if (Collision::IsCollide(broadphase, collidableEntity.at(index)->GetBound()))
			{
				if (collidableEntity.at(index)->GetEntityId() == EntityId::DownPlatform_ID) {
					int a = 0;
				}
				Entity::CollisionReturn collideData;
				float collisionTime = Collision::SweptAABB(player, collidableEntity.at(index), collideData);
				if (collisionTime < 1.0f) //collisiontime > 0 &&
				{
					Entity::CollisionSide sidePlayer = Collision::GetSideCollision(player, collideData);
					Entity::CollisionSide sideImpactor = Collision::GetSideCollision(collidableEntity.at(index), collideData);

					player->OnCollision(collidableEntity.at(index), sidePlayer, collideData);
					collidableEntity.at(index)->OnCollision(player, sideImpactor, collideData);

					if (collidableEntity.at(index)->GetEntityId() == EntityId::Door_ID) {
						currentDoor = (Door *)collidableEntity.at(index);
					}

					if (collidableEntity.at(index)->GetEntityId() == EntityId::CheckPoint_ID) {
						checkPoint = collidableEntity.at(index);
					}

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
		
	}

	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING) {
		player->OnNoCollisionWithBottom();
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
