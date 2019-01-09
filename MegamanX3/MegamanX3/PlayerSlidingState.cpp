#include "pch.h"
#include "PlayerSlidingState.h"
#include "Engine.h"
#include "EntityImport.h"

PlayerSlidingState::PlayerSlidingState(PlayerStateHandler * handler, Player * entity) : PlayerState(handler, entity)
{

	slideSprite = new AnimatedSprite(15, 2.0f, false);
	slideSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		73, 74, 10, 50, 50);

	fireSprite = new AnimatedSprite(15, 2.0f, false);
	fireSprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "x",
		75, 76, 10, 50, 50);
}


PlayerSlidingState::~PlayerSlidingState()
{
	if (handler->GetCurrentStateName() != PlayerStateHandler::StateName::Sliding) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void PlayerSlidingState::Load()
{
	sprite = slideSprite;
	entity->SetSprite(sprite);
	entity->AllowJump();
	if (entity->GetReverse()) {
		acceleratorX = -30.0f;
	}
	else {
		acceleratorX = 30.0f;
	}
	slidedDistance = 0;
}

void PlayerSlidingState::Update()
{	
	entity->AddVelocityX(acceleratorX);
	slidedDistance += abs(acceleratorX / 3.0f);
	if (slidedDistance >= Define::MAX_SLIDE_DISTANCE) {
		handler->ChangeState(PlayerStateHandler::Standing);
		slidedDistance = 0;
	}
}

void PlayerSlidingState::UpdateInput()
{
	Input *input = Engine::GetEngine()->GetInput();
	if (input == nullptr) {
		return;
	}

	if (input->IsKeyUp(DIK_J)) {
		entity->fireCoolDown = 0;
		sprite = fireSprite;
		entity->SetSprite(sprite);
		entity->Shoot();
	}
	else {
		if (entity->fireCoolDown < 20) {
			entity->fireCoolDown++;
		}
		else {
			sprite = slideSprite;
			entity->SetSprite(sprite);
		}
	}

	if (input->IsKeyDown(DIK_J)) {
		entity->bulletCharging++;
	}
}

void PlayerSlidingState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (impactor->GetEntityId())
	{
	case Platform_ID:
	case Door_ID:
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
	default:
		break;
	}

}

void PlayerSlidingState::OnPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side) {
	case Entity::Left:
	{
		//va cham phia ben trai player
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToLeft)
		{
			//day Player ra phia ben phai de cho player khong bi xuyen qua object
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

			handler->ChangeState(PlayerStateHandler::Standing);
		}

		return;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
		{
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			handler->ChangeState(PlayerStateHandler::Standing);
		}
		return;
	}

	case Entity::Top:
		break;

	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		entity->SetVelocityY(0);

		return;
	}
	}
}

void PlayerSlidingState::OnRoofCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	switch (side) {
	case Entity::Left:
	{
		//va cham phia ben trai player
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToLeft)
		{
			//day Player ra phia ben phai de cho player khong bi xuyen qua object
			entity->AddPosition(-5, -5);
			//handler->ChangeState(PlayerStateHandler::Standing);
		}

		return;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player
		if (handler->GetMoveDirection() == PlayerStateHandler::MoveToRight)
		{
			entity->AddPosition(5, -5);
			//handler->ChangeState(PlayerStateHandler::Standing);
		}
		return;
	}

	case Entity::Top:
		break;

	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		entity->SetPosition(entity->GetPosition().x, ((Roof *)impactor)->GetCollidePosition(entity) - entity->GetWidth() / 2);
		entity->SetVelocityY(0);
		return;
	}
	}
}

void PlayerSlidingState::OnUpPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
		entity->SetPosition(entity->GetPosition().x, ((UpPlatform *)impactor)->GetCollidePosition(entity) - entity->GetWidth() / 2 - 20);
		entity->SetVelocityY(0);
		return;
	}
	}
}

void PlayerSlidingState::OnDownPlatformCollide(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
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
		entity->SetPosition(entity->GetPosition().x, ((DownPlatform *)impactor)->GetCollidePosition(entity) - entity->GetWidth() / 2 - 20);
		entity->SetVelocityY(0);
		return;
	}
	}
}

