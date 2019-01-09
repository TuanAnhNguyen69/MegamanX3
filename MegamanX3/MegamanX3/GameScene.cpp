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
	//player->SetPosition(2614 * 4, 566 * 4);
	player->SetPosition(15450, 3850);
	camera->SetCenter(player->GetPosition());

	EntityManager::GetInstance()->Initialize(player, camera, "blast_hornet_state", map->GetWidth(), map->GetHeight());	

	Sound::getInstance()->loadSound((char*)"sound/aircraft.wav", "aircraft");
	Sound::getInstance()->loadSound((char*)"sound/BlastHornet.wav", "blasthornet");
	Sound::getInstance()->loadSound((char*)"sound/explosion.wav", "explosion");
	Sound::getInstance()->loadSound((char*)"sound/health_up.wav", "health_up");
	Sound::getInstance()->loadSound((char*)"sound/item.wav", "item");
	Sound::getInstance()->loadSound((char*)"sound/normal_bullet.wav", "normal_bullet");
	Sound::getInstance()->loadSound((char*)"sound/player_climb.wav", "player_climb");
	Sound::getInstance()->loadSound((char*)"sound/player_damaged.wav", "player_damaged");
	Sound::getInstance()->loadSound((char*)"sound/player_die.wav", "player_die");
	Sound::getInstance()->loadSound((char*)"sound/player_load_power.wav", "blasthornet");
	Sound::getInstance()->loadSound((char*)"sound/power_bullet.wav", "power_bullet");
	Sound::getInstance()->loadSound((char*)"sound/shoot_canon.wav", "shoot_canon");
	Sound::getInstance()->loadSound((char*)"sound/shoot_rocket.wav", "shoot_rocket");

	x_health = new HealthBar(EntityId::HealthX_ID);
	boss_health = new HealthBar(EntityId::HealthBoss_ID);
	
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

	if (currentBoss && currentBoss->GetHP() > 0) {
		doorLock = true;
	}
	else {
		doorLock = false;
	}

	if (checkPoint) {
			std::cout << "vel" << checkPoint->GetVelocity().x << std::endl;
			std::cout << "posX" << checkPoint->GetPosition().x << std::endl;
			std::cout << "posY" << checkPoint->GetPosition().y << std::endl;
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

	x_health->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
		SCREEN_HEIGHT / 2 - camera->GetCenter().y);
	x_health->Update(player->GetHP(), camera->GetCenter());

	/*boss_health->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
		SCREEN_HEIGHT / 2 - camera->GetCenter().y);
	boss_health->Update(currentBoss->GetHP(), camera->GetCenter());*/
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
	
	auto list = EntityManager::GetInstance()->GetAllEntities();
	//for (int index = 0; index < list.size(); index++) {
	//	debugDraw->DrawRect(list.at(index)->GetBound(), camera);
	//}
	EntityManager::GetInstance()->Render();
	//DrawQuadtree(EntityManager::GetInstance()->GetQuadTree());
	x_health->Render();
	//boss_health->Render();
}
