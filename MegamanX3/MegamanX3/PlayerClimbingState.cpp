#include "pch.h"
#include "PlayerClimbingState.h"
#include "Engine.h"


PlayerClimbingState::PlayerClimbingState(PlayerStateHandler *handler, Entity *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.5, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		49, 50, 10, 50, 50);
}


PlayerClimbingState::~PlayerClimbingState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Climbing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerClimbingState::Load()
{
	entity->SetSprite(sprite);
	acceleratorX = 8.0f;
	acceleratorY = 7.0f;
	sprite->ResetFrame();
}

void PlayerClimbingState::Update()
{
	entity->AddVelocityY(acceleratorY);
	if (entity->GetVelocity().y > Define::PLAYER_MAX_JUMP_VELOCITY) {
		entity->SetVelocityY(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

void PlayerClimbingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyDown(DIK_J)) {
		sprite->SetFrameRange(54, 55);
	}
	else {
		sprite->SetFrameRange(50, 50);
	}

	if ((input->IsKeyDown(DIK_A) && climbingType == ClimbingLeft))
	{
		entity->SetReverse(true);
	}
	else
	{
		entity->SetVelocityX(0.01f);
		//handler->ChangeState(PlayerStateHandler::StateName::Falling);
		//return;
	}

	if ((input->IsKeyDown(DIK_D) && climbingType == ClimbingRight))
	{
		entity->SetReverse(false);
	}
	else
	{
		entity->SetReverse(-0.01f);
		//handler->ChangeState(PlayerStateHandler::StateName::Falling);
		//return;
	}

	if (input->IsKeyDown(DIK_SPACE))
	{
		handler->ChangeState(PlayerStateHandler::StateName::Jumping);
	}

}

void PlayerClimbingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	Input *input = Engine::GetEngine()->GetInput();
	switch (side)
	{
	case Entity::SideCollisions::Left:
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToLeft)
		{
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			entity->SetVelocityX(0);
		}
		if (input->IsKeyDown(DIK_A))
		{
			climbingType = ClimbingLeft;
		}
		else
		{
			handler->ChangeState(PlayerStateHandler::StateName::Falling);
		}
		break;
	case Entity::SideCollisions::Right:
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
		{
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			entity->SetVelocityX(0);
		}
		if (input->IsKeyDown(DIK_D))
		{
			climbingType = ClimbingRight;
		}
		else
		{
			handler->ChangeState(PlayerStateHandler::StateName::Falling);
		}
		break;
	case Entity::SideCollisions::Top:
		break;
	case Entity::SideCollisions::Bottom:
	//case Entity::TopRight:
	//case Entity::BottomLeft:
		isStanding = true;
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			if (isKeyLeft || isKeyRight)
			{
				handler->ChangeState(PlayerStateHandler::Running);
			}
			else
			{
				handler->ChangeState(PlayerStateHandler::Standing);
			}
		}
		return;
		break;
	default:
		break;
	}
}