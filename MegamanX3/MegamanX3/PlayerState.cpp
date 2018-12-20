#include "pch.h"
#include "PlayerState.h"
#include "Player.h"


PlayerState::PlayerState(PlayerStateHandler *handler, Player *entity)
{
	this->handler = handler;
	this->entity = entity;
}

PlayerState::~PlayerState()
{
}

void PlayerState::Load()
{

}

void PlayerState::Update()
{
}

void PlayerState::UpdateInput()
{
}

void PlayerState::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
