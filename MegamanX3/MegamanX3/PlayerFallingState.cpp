  #include "pch.h"
#include "PlayerFallingState.h"
#include "Engine.h"
#include "Roof.h"

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
	entity->SetSprite(sprite);
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;
	isLeftOrRightKeyPressed = false;
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
		if (blockType == BlockRight)
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
		if (blockType == BlockLeft)
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
			OnPlatformCollide(impactor, side, data);
			break;
		case Roof_ID:
			OnRoofCollide(impactor, side, data);
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
			blockType = BlockLeft;
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			entity->SetVelocityX(0);
		}
		entity->isJumping = false;
		break;

	case Entity::Right:
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
		{
			blockType = BlockRight;
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
		blockType = None;
		entity->isJumping = false;
		return;

	default:
		blockType = None;
		break;
	}
}

void PlayerFallingState::OnRoofCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	std::cout << ((Roof*)impactor)->GetCollidePosition(entity) << std::endl;

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
			//if (entity->GetPosition().x < impactor->GetPosition().x + impactor->GetWidth() / 6
			//	&& entity->GetPosition().x > impactor->GetPosition().x - impactor->GetWidth() / 6)
			//{
			//	entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			//	acceleratorY = 0.0f;
			//	isFalling = false;
			//}
			//else if (entity->GetPosition().x < impactor->GetPosition().x - impactor->GetWidth() / 6) {
			//	if (entity->GetPosition().y + entity->GetHeight() / 2 >= impactor->GetPosition().y) {
			//		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			//		acceleratorY = 0.0f;
			//		isFalling = false;
			//	}
			//}
			//else if (entity->GetPosition().x > impactor->GetPosition().x + impactor->GetWidth() / 6) {
			//	if (entity->GetPosition().y + entity->GetHeight() / 2 >= impactor->GetPosition().y) {
			//		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			//		acceleratorY = 0.0f;
			//		isFalling = false;
			//	}
			//}
			if (entity->GetPosition().y + entity->GetHeight() / 2 >= ((Roof*)impactor)->GetCollidePosition(entity)) {
				acceleratorY = 0.0f;
				isFalling = false;
			}
		}
		blockType = None;
		entity->isJumping = false;
		return;

	default:
		blockType = None;
		break;
	}
}

