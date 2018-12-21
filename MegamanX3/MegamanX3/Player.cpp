#include "pch.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"
#include "PlayerSlidingState.h"
#include "PlayerDamagedState.h"
#include "PlayerClimbingState.h"
#include "PlayerBullet.h"

#include <iostream>

Player::Player() : Entity(EntityId::Megaman_ID)
{
	//entity = nullptr;
	currentState = nullptr;
	standingState = nullptr;
	runningState = nullptr;
	jumpingState = nullptr;
	fallingState = nullptr;
	slidingState = nullptr;
	damagedState = nullptr;
	climbingState = nullptr;
	this->bulletCharging = 0;
	this->fireCoolDown = 10;
}


Player::~Player()
{
	if (standingState) {
		delete standingState;
		standingState = nullptr;
	}

	if (runningState) {
		delete runningState;
		runningState = nullptr;
	}
}

void Player::Initialize(LPDIRECT3DDEVICE9 device, Camera *camera)
{
	this->camera = camera;

	this->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->SetScale(2, 2);
	this->SetBound(60,100);

	chargerSuper = new Entity();
	AnimatedSprite *chargeSuperSprite = new AnimatedSprite(15, 1.5, true);
	chargeSuperSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "charging",
		1, 14, 7, 100, 100);
	chargerSuper->SetSprite(chargeSuperSprite);

	chargerExtreme = new Entity();
	AnimatedSprite *chargeExtremeSprite = new AnimatedSprite(15, 1.5, true);
	chargeExtremeSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "charging",
		14, 24, 7, 100, 100);
	chargerExtreme->SetSprite(chargeExtremeSprite);


	standingState = new PlayerStandingState(this, this);
	runningState = new PlayerRunningState(this, this);
	jumpingState = new PlayerJumpingState(this, this);
	fallingState = new PlayerFallingState(this, this);
	slidingState = new PlayerSlidingState(this, this);
	damagedState = new PlayerDamagedState(this, this);
	climbingState = new PlayerClimbingState(this, this);
	ChangeState(Falling);
	isJumping = true;
	allowSlide = true;
}

void Player::Update()
{
	if (camera) {
		this->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
			SCREEN_HEIGHT / 2 - camera->GetCenter().y);
		this->chargerSuper->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
			SCREEN_HEIGHT / 2 - camera->GetCenter().y);
		this->chargerExtreme->SetTranslation(SCREEN_WIDTH / 2 - camera->GetCenter().x,
			SCREEN_HEIGHT / 2 - camera->GetCenter().y);
	}

	chargerSuper->SetPosition(this->GetPosition().x, this->GetPosition().y + 10);
	chargerExtreme->SetPosition(this->GetPosition().x, this->GetPosition().y + 10);


	if (currentState) {
		currentState->UpdateInput();
		currentState->Update();
	}

	if (bulletCharging < 50) {
		bulletDamage = 2;
	}
	else if (bulletCharging >= 50 && bulletCharging < 150) {
		chargerSuper->Update();
		bulletDamage = 3;
	}
	else {
		chargerExtreme->Update();
		bulletDamage = 10;
	}

	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_H)) {
		ChangeState(Damaged);
	}

	if (input->IsKeyDown(DIK_Z)) {
		if (allowSlide) {
			ChangeState(Sliding);
			allowSlide = false;
		}
	}

	if (input->IsKeyUp(DIK_Z)) {
		ChangeState(Standing);
		allowSlide = true;
	}

	if (input->IsKeyDown(DIK_SPACE)) {
		if (!isJumping) {
			if (currentStateName == Running || currentStateName == Standing) {
				ChangeState(Jumping);
			}
			isJumping = true;
		}
	}
	
	if (input->IsKeyUp(DIK_SPACE)) {
		if (currentStateName == Jumping) {
			ChangeState(Falling);
		}
	}

	Entity::Update();
}

//void Player::SetPosition(int x, int y)
//{
//	entity->SetPosition(x, y);
//}
//
//D3DXVECTOR3 Player::GetPosition()
//{
//	return entity->GetPosition();
//}
//
//Entity * Player::GetEntity()
//{
//	return entity;
//}

PlayerStateHandler::StateName Player::GetCurrentStateName() {
	return this->currentStateName;
}

void Player::ChangeState(PlayerStateHandler::StateName stateName) {
	switch (stateName) {
	case Standing:
		currentState = standingState;
		currentStateName = Standing;
		break;
	case Running:
		currentState = runningState;
		currentStateName = Running;
		break;
	case Jumping:
		currentState = jumpingState;
		currentStateName = Jumping;
		break;
	case Falling:
		currentState = fallingState;
		currentStateName = Falling;
		break;
	case Sliding:
		currentState = slidingState;
		currentStateName = Sliding;
		break;
	case Damaged:
		currentState = damagedState;
		currentStateName = Damaged;
		break;
	case Climbing:
		currentState = climbingState;
		currentStateName = Climbing;
		break;
	}
	currentState->Load();
}

PlayerStateHandler::MoveDirection Player::GetMoveDirection() {
	if (this->GetVelocity().x > 0) {
		return MoveDirection::MoveToRight;
	}
	else if (this->GetVelocity().x < 0) {
		return MoveDirection::MoveToLeft;
	}
	return MoveDirection::None;
}

void Player::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::MegamanBullet_ID) {
		return;
	}

	if (currentState) {
		currentState->OnCollision(impactor, side, data);
	}
}

void Player::OnNoCollisionWithBottom()
{
	if (currentStateName != Jumping && currentStateName != Falling && currentStateName != Climbing) {
		ChangeState(Falling);
	}
}

void Player::Shoot()
{
	PlayerBullet *bullet = new PlayerBullet();
	bullet->Initialize(bulletDamage);
	bullet->SetPosition(this->GetPosition().x, this->GetPosition().y + 10);
	bullet->SetReverse(this->GetReverse());

	float accelX = 0;
	if (this->GetReverse()) {
		accelX = -700.0;
	}
	else {
		accelX = 700.0;
	}

	bullet->SetVelocity(this->GetVelocity().x + accelX, 0);
	bullet->SetScale(2, 2);
	EntityManager::GetInstance()->AddEntity(bullet);
	this->bulletCharging = 0;
}

void Player::ChangeBulletState()
{
	if (bulletCharging < 10) {
		return;
	}
	else {
		return;
	}
}

void Player::Render()
{
	Entity::Render();
	if (bulletCharging >= 50 && bulletCharging < 150) {
		chargerSuper->Render();
	}
	else if (bulletCharging >= 150) {
		chargerExtreme->Render();
	}
}
