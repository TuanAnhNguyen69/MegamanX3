#include "pch.h"
#include "PlayerStandingState.h"
#include "AnimatedSprite.h"
#include "Engine.h"
#include "PlayerBullet.h"
#include "EntityImport.h"

PlayerStandingState::PlayerStandingState(PlayerStateHandler *handler, Player *entity) : PlayerState(handler, entity)
{
	standSprite = new AnimatedSprite(15, 0.3, true);
	standSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		7, 9, 10, 50, 50);
	shootSprite = new AnimatedSprite(15, 0.5, true);
	shootSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		11, 12, 10, 50, 50);
	sprite = standSprite;
}

PlayerStandingState::~PlayerStandingState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Standing) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerStandingState::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	entity->SetMovable(true);
	entity->AllowJump();
}

void PlayerStandingState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (impactor->GetEntityId()) {
	case EntityId::Platform_ID:
		OnPlatformCollide(impactor, side, data);
		break;
	case EntityId::LeftBlueConveyor_ID:
	case EntityId::RightBlueConveyor_ID:
	case EntityId::LeftYellowConveyor_ID:
	case EntityId::RightYellowConveyor_ID:
	case EntityId::LeftSmallConveyor_ID:
	case EntityId::RightSmallConveyor_ID:
		OnConveyorCollision(impactor, side, data);
		break;
	default:
		break;
	}
}

void PlayerStandingState::OnPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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

void PlayerStandingState::OnConveyorCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
		entity->SetVelocityY(0);
		entity->SetVelocityX(((Conveyor*)(impactor))->GetSpeed() * 4);
		break;
	default:
		break;
	}
}

void PlayerStandingState::Update()
{

}

void PlayerStandingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyUp(DIK_J)) {
		entity->fireCoolDown = 0;
		sprite = shootSprite;
		entity->SetSprite(sprite);
		entity->Shoot();
	}
	else {
		if (entity->fireCoolDown < 20) {
			entity->fireCoolDown++;
		}
		else {
			sprite = standSprite;
			entity->SetSprite(sprite);
		}	
	}

	if (input->IsKeyDown(DIK_J)) {
		entity->bulletCharging++;
	}

	if (input->IsKeyDown(DIK_D) || input->IsKeyDown(DIK_A)) {
		handler->ChangeState(PlayerStateHandler::StateName::Running);
	}
}

