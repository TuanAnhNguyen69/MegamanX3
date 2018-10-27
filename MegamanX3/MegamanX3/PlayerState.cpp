#include "pch.h"
#include "PlayerState.h"


PlayerState::PlayerState(PlayerStateHandler *handler, Entity *entity)
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
