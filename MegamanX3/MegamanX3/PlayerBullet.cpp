#include "pch.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet() : Entity(EntityId::MegamanBullet_ID)
{
	
}

void PlayerBullet::Initialize()
{
}

void PlayerBullet::Update()
{
}

void PlayerBullet::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}


PlayerBullet::~PlayerBullet()
{
}
