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

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->Initialize("blast_hornet_state");

	player = new Player();
	player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), camera);
	player->SetPosition(8736, 2151);
	camera->SetCenter(player->GetPosition());

	EntityManager::GetInstance()->Initialize(player, camera, "blast_hornet_state", map->GetWidth(), map->GetHeight());

	Sound::getInstance()->loadSound((char*)"sound/normal_bullet.wav", "normal_Bullet");
	Sound::getInstance()->setVolume(120.0f, "normal_Bullet");

	Sound::getInstance()->loadSound((char*)"sound/soundtrack.wav", "soundtrack");
	Sound::getInstance()->setVolume(90.0f, "soundtrack");

	x_health = new HealthX(player);
	x_health->SetPosition(player->GetPosition().x - 100, player->GetPosition().y - 100);
	x_health->SetBound(14, 52);

	Sound::getInstance()->play("soundtrack", true, 0);

	debugDraw = new DebugDraw();
	debugDraw->SetColor(D3DCOLOR_XRGB(50, 96, 55));
	debugDraw->SetLineSize(5);

	doorLock = false;

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
	player->Revive();
	camera->SetCenter(player->GetPosition());
}

void GameScene::Update()
{
	if (player->NeedRevive()) {
		Revive();
	}

	if (currentBoss) {
		if (currentBoss->GetEntityId() == Cargo_ID) {
			camera->Lock();
			doorLock = true;
		}
		else if (currentBoss->GetHP() > 0) {
			doorLock = true;
		}
		else {
			doorLock = false;
			currentBoss = nullptr;
		}
	}
	else {
		camera->Unlock();
		doorLock = false;
	}

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
	x_health->Update();
	EntityManager::GetInstance()->Update();
}

void GameScene::CheckCollision()
{
	int widthBottom = 0;
	std::vector<Entity*> collidableEntity;
	EntityManager::GetInstance()->GetQuadTree()->GetEntitiesCollideAble(collidableEntity, camera->GetBound());
	int size = collidableEntity.size();
	for (size_t index = 0; index < size; index++) {
		if (Collision::IsCollide(collidableEntity.at(index)->GetBound(), camera->GetBound())) {
			if (collidableEntity.at(index)->GetEntityId() == EntityId::BlastHornet_ID
				|| collidableEntity.at(index)->GetEntityId() == EntityId::Byte_ID
				|| collidableEntity.at(index)->GetEntityId() == EntityId::Shurikein_ID
				|| collidableEntity.at(index)->GetEntityId() == EntityId::Cargo_ID) {
				if (((Enemy *)collidableEntity.at(index))->IsActive()) {
					currentBoss = (Enemy *)collidableEntity.at(index);
				}
			}

			RECT broadphase = Collision::GetSweptBroadphaseRect(player);
			if (Collision::IsCollide(broadphase, collidableEntity.at(index)->GetBound()))
			{
				Entity::CollisionReturn collideData;
				float collisionTime = Collision::SweptAABB(player, collidableEntity.at(index), collideData);
				if (collisionTime < 1.0f) //collisiontime > 0 &&
				{
					if (collidableEntity.at(index)->GetEntityId() == EntityId::Door_ID) {
						currentDoor = (Door *)collidableEntity.at(index);
						currentDoor->SetLock(doorLock);
					}

					Entity::CollisionSide sidePlayer = Collision::GetSideCollision(player, collideData);
					Entity::CollisionSide sideImpactor = Collision::GetSideCollision(collidableEntity.at(index), collideData);

					player->OnCollision(collidableEntity.at(index), sidePlayer, collideData);
					collidableEntity.at(index)->OnCollision(player, sideImpactor, collideData);

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
	x_health->Render();
	auto list = EntityManager::GetInstance()->GetAllEntities();
	for (int index = 0; index < list.size(); index++) {
		debugDraw->DrawRect(list.at(index)->GetBound(), camera);
	}
	EntityManager::GetInstance()->Render();
	DrawQuadtree(EntityManager::GetInstance()->GetQuadTree());
}