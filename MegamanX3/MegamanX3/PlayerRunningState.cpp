#include "pch.h"
#include "PlayerRunningState.h"
#include "Engine.h"

PlayerRunningState::PlayerRunningState(PlayerStateHandler *handler, Player *entity) : PlayerState(handler, entity)
{
	sprite = new AnimatedSprite(15);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		14, 23, 10, 50, 50);
}


PlayerRunningState::~PlayerRunningState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Running) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerRunningState::Load()
{
	entity->SetSprite(sprite);
	acceleratorX = 25.0f;
}

void PlayerRunningState::Update()
{

}

void PlayerRunningState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyUp(DIK_J)) {
		entity->fireCoolDown = 0;
		sprite->SetFrameRange(24, 33);
		entity->Shoot();
	}
	else {
		if (entity->fireCoolDown < 20) {
			entity->fireCoolDown++;
		}
		else {
			sprite->SetFrameRange(14, 23);
		}
	}

	if (input->IsKeyDown(DIK_J)) {
		entity->bulletCharging++;
	}

	if (input->IsKeyDown(DIK_D)) {
		entity->SetReverse(false);
		if (entity->GetVelocity().x < Define::PLAYER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(acceleratorX);
			if (entity->GetVelocity().x >= Define::PLAYER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (input->IsKeyDown(DIK_A)) {
		entity->SetReverse(true);
		if (entity->GetVelocity().x > -Define::PLAYER_MAX_RUNNING_SPEED) {
			entity->AddVelocityX(-acceleratorX);
			if (entity->GetVelocity().x < -Define::PLAYER_MAX_RUNNING_SPEED) {
				entity->SetVelocityX(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else {
		handler->ChangeState(PlayerStateHandler::StateName::Standing);
	}
}

void PlayerRunningState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side) {
	case Entity::Left:
	{
		//va cham phia ben trai player
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToLeft)
		{
			//day Player ra phia ben phai de cho player khong bi xuyen qua object
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

			//handler->ChangeState(PlayerStateHandler::Standing);
		}

		return;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
		{
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			//handler->ChangeState(PlayerStateHandler::Standing);
		} 
		return;
	}

	case Entity::Top:
		break;

	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

		entity->SetVelocityY(0);

		return;
	}
	}
}

