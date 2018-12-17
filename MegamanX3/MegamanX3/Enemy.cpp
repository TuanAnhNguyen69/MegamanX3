#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(EntityId entityId, Player * player) : Entity(entityId)
{
	this->player = player;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	int a = 0;
}

void Enemy::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}
