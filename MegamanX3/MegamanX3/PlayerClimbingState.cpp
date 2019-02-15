#include "pch.h"
#include "PlayerClimbingState.h"
#include "Engine.h"

PlayerClimbingState::PlayerClimbingState(PlayerStateHandler *handler, Player *entity) : PlayerState(handler, entity)
{
	climbSprite = new AnimatedSprite(15, 0.5, false);
	climbSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		49, 50, 10, 50, 50);

	fireSprite = new AnimatedSprite(15, 0.5, false);
	fireSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		54, 55, 10, 50, 50);
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
	sprite = climbSprite;
	entity->SetSprite(sprite);
	acceleratorX = 8.0f;
	acceleratorY = 7.0f;
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

	if (input->IsKeyUp(DIK_J)) {
		entity->fireCoolDown = 0;
		sprite = fireSprite;
		entity->SetSprite(fireSprite);
		entity->Shoot();
	}
	else {
		if (entity->fireCoolDown < 20) {
			entity->fireCoolDown++;
		}
		else {
			sprite = climbSprite;
			entity->SetSprite(climbSprite);
		}
	}

	if (input->IsKeyDown(DIK_J)) {
		entity->bulletCharging++;
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

void PlayerClimbingState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() != Platform_ID && impactor->GetEntityId() != Door_ID && impactor->GetEntityId() != Door_ID) {
		return;
	}
	switch (impactor->GetEntityId())
	{
	case Platform_ID:
	case Door_ID:
	case EntityId::LeftBlueConveyor_ID:
	case EntityId::RightBlueConveyor_ID:
	case EntityId::LeftYellowConveyor_ID:
	case EntityId::RightYellowConveyor_ID:
	case EntityId::LeftSmallConveyor_ID:
	case EntityId::RightSmallConveyor_ID:
		OnPlatformCollision(impactor, side, data);
		break;
	default:
		break;
	}

	
}

void PlayerClimbingState::OnPlatformCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	Input *input = Engine::GetEngine()->GetInput();
	switch (side)
	{
	case Entity::CollisionSide::Left:
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
			entity->blockType = Player::BlockType::None;
		}
		break;
	case Entity::CollisionSide::Right:
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
			entity->blockType = Player::BlockType::None;
		}
		break;
	case Entity::CollisionSide::Top:
		break;
	case Entity::CollisionSide::Bottom:
		//case Entity::TopRight:
		//case Entity::BottomLeft:
		isStanding = true;
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			if (isKeyLeft || isKeyRight)
			{
				handler->ChangeState(PlayerStateHandler::Running);
				entity->blockType = Player::BlockType::None;
			}
			else
			{
				handler->ChangeState(PlayerStateHandler::Standing);
				entity->blockType = Player::BlockType::None;
			}
		}
		break;
	default:
		handler->ChangeState(PlayerStateHandler::StateName::Falling);
		entity->blockType = Player::BlockType::None;
		break;
	}
}
