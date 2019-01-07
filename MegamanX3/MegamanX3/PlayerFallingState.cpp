  #include "pch.h"
#include "PlayerFallingState.h"
#include "Engine.h"
#include "EntityImport.h"

PlayerFallingState::PlayerFallingState(PlayerStateHandler *handler, Player *entity) : PlayerState(handler, entity)
{
	fallSprite = new AnimatedSprite(15, 0.5, false);
	fallSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		37, 38, 10, 50, 50);

	landingSprite = new AnimatedSprite(15, 0.5, false);
	landingSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		39, 40, 10, 50, 50);

	fireSprite = new AnimatedSprite(15, 0.5, false);
	fireSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		44, 45, 10, 50, 50);

	landingFireSprite = new AnimatedSprite(15, 0.5, false);
	landingFireSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		46, 47, 10, 50, 50);
	fallDistance = 0;
}


PlayerFallingState::~PlayerFallingState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Falling) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerFallingState::Load()
{
	sprite = fallSprite;
	isFalling = true;
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;
	isLeftOrRightKeyPressed = false;
	entity->SetSprite(sprite);
	sprite->ResetFrame();
}

void PlayerFallingState::Update()
{
	if (!isFalling) {
		if (sprite->IsFinished()) {
			if (isLeftOrRightKeyPressed)
			{
				handler->ChangeState(PlayerStateHandler::Running);
			}
			else
			{
				handler->ChangeState(PlayerStateHandler::Standing);
			}
		}
	}

	entity->AddVelocityY(acceleratorY);
	if (entity->GetVelocity().y > Define::PLAYER_MAX_JUMP_VELOCITY) {
		entity->SetVelocityY(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

void PlayerFallingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyUp(DIK_J)) {
		entity->fireCoolDown = 0;
		if (isFalling) {
			sprite = fireSprite;
		}
		else {
			sprite = landingFireSprite;
		}
		entity->SetSprite(sprite);
		entity->Shoot();
	}
	else {
		if (entity->fireCoolDown < 20) {
			entity->fireCoolDown++;
		}
		else {
			if (isFalling) {
				sprite = fallSprite;
			}
			else {
				sprite = landingSprite;
			}
			entity->SetSprite(sprite);
		}
	}

	if (input->IsKeyDown(DIK_D)) {
		isLeftOrRightKeyPressed = true;
		entity->SetReverse(false);
		if (entity->GetVelocity().x < Define::PLAYER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x >= Define::PLAYER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
		if (entity->blockType == Player::BlockRight)
		{
			handler->ChangeState(PlayerStateHandler::StateName::Climbing);
			return;
		}
	}
	else if (input->IsKeyDown(DIK_A)) {
		isLeftOrRightKeyPressed = true;
		entity->SetReverse(true);
		if (entity->GetVelocity().x > -Define::PLAYER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < -Define::PLAYER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
		if (entity->blockType == Player::BlockLeft)
		{
			handler->ChangeState(PlayerStateHandler::StateName::Climbing);
			return;
		}
	}
	else {
		isLeftOrRightKeyPressed = false;
	}
}

void PlayerFallingState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (impactor->GetEntityId()) {
		case Platform_ID:
		case EntityId::LeftBlueConveyor_ID:
		case EntityId::RightBlueConveyor_ID:
		case EntityId::LeftYellowConveyor_ID:
		case EntityId::RightYellowConveyor_ID:
		case EntityId::LeftSmallConveyor_ID:
		case EntityId::RightSmallConveyor_ID:
			OnPlatformCollide(impactor, side, data);
			break;
		case Roof_ID:
			OnRoofCollide(impactor, side, data);
			break;
		case UpPlatform_ID:
			OnUpPlatformCollide(impactor, side, data);
			break;
		case DownPlatform_ID:
			OnDownPlatformCollide(impactor, side, data);
			break;
	}
}

void PlayerFallingState::OnPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToLeft)
		{
			entity->blockType = Player::BlockLeft;
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			entity->SetVelocityX(0);
		}
		entity->isJumping = false;
		break;

	case Entity::Right:
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
		{
			entity->blockType = Player::BlockRight;
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			entity->SetVelocityX(0);
		}
		entity->isJumping = false;
		break;

	case Entity::Top:
		entity->isJumping = false;
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			acceleratorY = 0.0f;
			isFalling = false;
		}
		entity->blockType = Player::None;
		entity->isJumping = false;
		return;

	default:
		entity->blockType = Player::None;
		break;
	}
}

void PlayerFallingState::OnRoofCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
		break;
	case Entity::Right:
		break;
	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			if (entity->GetPosition().y + entity->GetHeight() / 2 >= ((Roof*)impactor)->GetCollidePosition(entity) + 20) {
				acceleratorY = 0.0f;
				isFalling = false;
			}
		}
		entity->blockType = Player::None;
		entity->isJumping = false;
		return;

	default:
		entity->blockType = Player::None;
		break;
	}
}

void PlayerFallingState::OnUpPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
		break;
	case Entity::Right:
		break;
	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			if (entity->GetPosition().y + entity->GetHeight() / 2 >= ((UpPlatform*)impactor)->GetCollidePosition(entity)) {
				acceleratorY = 0.0f;
				isFalling = false;
			}
		}
		entity->blockType = Player::None;
		entity->isJumping = false;
		return;

	default:
		entity->blockType = Player::None;
		break;
	}
}

void PlayerFallingState::OnDownPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
		break;
	case Entity::Right:
		break;
	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			if (entity->GetPosition().y + entity->GetHeight() / 2 >= ((DownPlatform*)impactor)->GetCollidePosition(entity)) {
				acceleratorY = 0.0f;
				isFalling = false;
			}
		}
		entity->blockType = Player::None;
		entity->isJumping = false;
		return;

	default:
		entity->blockType = Player::None;
		break;
	}
}

