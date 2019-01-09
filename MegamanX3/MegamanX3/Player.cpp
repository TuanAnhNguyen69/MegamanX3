#include "pch.h"
#include "pch.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"
#include "PlayerSlidingState.h"
#include "PlayerDamagedState.h"
#include "PlayerClimbingState.h"
#include "PlayerReviveState.h"
#include "PlayerDieState.h"
#include "PlayerBullet.h"
#include "EntityImport.h"
#include "Collision.h"
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
	dieState = nullptr;
	reviveState = nullptr;
	
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
	dieState = new PlayerDieState(this, this);
	reviveState = new PlayerReviveState(this, this);

	ChangeState(Reviving);

	isJumping = true;
	allowSlide = true;
	movable = true;
	this->bulletCharging = 0;
	this->fireCoolDown = 10;
	this->hp = 30;
	autoMovedDistance = 0;
	reviving = false;
	noBottomCollide = false;
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

	if (immute && immuteTime < 80) {
		immuteTime++;
	}
	else {
		immute = false;
		immuteTime = 0;
	}


	if (!Collision::IsCollide(this->GetBound(), camera->GetBound()) && noBottomCollide) {
		hp = 0;
		SetVelocity(0, 0);
	}

	if (hp <= 0 && currentStateName != Dying) {
		ChangeState(Dying);
		movable = false;
	}

	if (!movable && currentStateName != Reviving) {
		SetVelocity(0, 0);
	}
	else {
		if (currentState) {
			currentState->UpdateInput();
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

		if (input->IsKeyUp(DIK_T)) {
			ChangeState(Damaged);
			hp -= 5;
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
	}

	if (currentState) {
		currentState->Update();
	}

	Entity::Update();
}

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
	case Dying:
		currentState = dieState;
		currentStateName = Dying;
		break;
	case Reviving:
		currentState = reviveState;
		currentStateName = Reviving;
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
	switch (impactor->GetEntityId()) {
	case EntityId::MegamanBullet_ID:
		return;	
	case EntityId::LeftBlueConveyor_ID:
	case EntityId::RightBlueConveyor_ID:
	case EntityId::LeftYellowConveyor_ID:
	case EntityId::RightYellowConveyor_ID:
	case EntityId::LeftSmallConveyor_ID:
	case EntityId::RightSmallConveyor_ID:
		OnConveyorCollision(impactor, side, data);
		break;
	case EntityId::BigElevator_ID:
		OnElevatorCollision(impactor, side, data);
		break;
	case EntityId::Door_ID:
		OnDoorCollision(impactor, side, data);
		break;
	case EntityId::GunnerRocket_ID:
	case EntityId::HeliRocket_ID:
	case EntityId::Canon_ID:
	case EntityId::Bee_ID:	
	case EntityId::BlastHornet_ID:
	case EntityId::Byte_ID:
	case EntityId::Helit_ID:
	case EntityId::NotorBanger_ID:
	case EntityId::Shurikein_ID:
	{
		if (immute) {
			return;
		}

		immute = true;
		ChangeState(Damaged);
		this->hp -= 2;
	}
	default:
		break;
	}

	if (currentState) {
		currentState->OnCollision(impactor, side, data);
	}
}

void Player::OnNoCollisionWithBottom()
{
	if (currentStateName != Jumping && currentStateName != Falling 
		&& currentStateName != Climbing && currentStateName != Reviving
		&& currentStateName != Dying) {
		ChangeState(Falling);
		noBottomCollide = true;
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

	if (currentStateName == Climbing) {
		accelX *= -1;
		bullet->SetReverse(!this->GetReverse());
	}

	bullet->SetVelocity(this->GetVelocity().x + accelX, 0);
	bullet->SetScale(2, 2);
	EntityManager::GetInstance()->AddEntity(bullet);
	switch(bulletDamage) {
	case 2:
	{
		Sound::getInstance()->play("normal_Bullet", false, 1);
		break;
	}
	case 3:
	{
		Sound::getInstance()->loadSound((char*)"sound/power_bullet.wav", "power_bullet");
		Sound::getInstance()->play("power_bullet", false, 1);
		break;
	}
	case 10:
	{
		Sound::getInstance()->loadSound((char*)"sound/power_bullet.wav", "power_bullet");
		Sound::getInstance()->play("power_bullet", false, 1);
		break;
	}

	}

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

void Player::AutoMoveFoward()
{
	int moveDistance = 1;
	autoMovedDistance += 1;
	if (GetReverse()) {
		moveDistance *= -1;
	}

	this->AddPosition(moveDistance, 0);
}

int Player::GetAutoMovedDistance()
{
	return autoMovedDistance;
}

bool Player::NeedRevive()
{
	return reviving;
}

void Player::RequireRevive()
{
	this->reviving = true;
}

bool Player::GetMovable()
{
	return movable;
}

void Player::SetMovable(bool movable)
{
	this->movable = movable;
	autoMovedDistance = 0;
}

void Player::SetImmute(bool immute)
{
	this->immute = true;
}

void Player::AllowJump()
{
	this->isJumping = false;
}

bool Player::IsImmute()
{
	return immute;
}

void Player::Revive()
{
	ChangeState(Reviving);
	isJumping = true;
	allowSlide = true;
	autoMovedDistance = 0;
	this->bulletCharging = 0;
	this->fireCoolDown = 10;
	this->hp = 30;
	reviving = false;
}

void Player::OnConveyorCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	case Entity::Right:
	case Entity::Top:
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
	default:
		break;
	}
}

void Player::OnDoorCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (((Door *)impactor)->IsLock()) {
		return;
	}

	switch (side)
	{
	case Entity::Left:
	case Entity::Right:
	{
		this->movable = false;
	}
	case Entity::Top:
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		break;
	default:
		break;
	}
}

void Player::OnElevatorCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	case Entity::Right:
	case Entity::Top:
		break;
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (((Elevator *)(impactor))->IsActive()) {
			this->AddPosition(0, ((Elevator *)(impactor))->GetSpeed());
		}
		SetVelocityY(0);
		break;
	default:
		break;
	}
}
