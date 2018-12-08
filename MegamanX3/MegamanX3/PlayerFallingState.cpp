  #include "pch.h"
#include "PlayerFallingState.h"
#include "Engine.h"

PlayerFallingState::PlayerFallingState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		37, 40, 10, 50, 50);
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
	entity->SetSprite(sprite);
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;
	isLeftOrRightKeyPressed = false;
	sprite->ResetFrame();
}

void PlayerFallingState::Update()
{
	entity->AddVelocityY(acceleratorY);
	if (entity->GetVelocity().y > Define::PLAYER_MAX_JUMP_VELOCITY) {
		entity->SetVelocityY(Define::PLAYER_MAX_JUMP_VELOCITY);
	}

	// For testing
	if (entity->GetPosition().y > (SCREEN_HEIGHT / 2)) {
	//	handler->ChangeState(PlayerStateHandler::StateName::Standing);
	}
}

void PlayerFallingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_J)) {
		sprite->SetFrameRange(44, 47);
	}
	else {
		sprite->SetFrameRange(37, 40);
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

void PlayerFallingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
		break;

	case Entity::Right:
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
		{
			blockType = BlockRight;
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			entity->SetVelocityX(0);
		}
		break;

	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			if (isLeftOrRightKeyPressed)
			{
				handler->ChangeState(PlayerStateHandler::Running);
			}
			else
			{
				handler->ChangeState(PlayerStateHandler::Standing);
			}
		}
		return;

	default:
		break;
	}
}
