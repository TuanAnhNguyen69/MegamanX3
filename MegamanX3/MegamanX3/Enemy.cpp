#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(EntityId entityId, Player * player) : Entity(entityId)
{
	this->player = player;
}


Enemy::~Enemy()
{
	delete this->player;
	this->player = nullptr;
}

void Enemy::Update()
{
	int a = 0;
}

void Enemy::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::MegamanBullet_ID)
	{
		
	}
}

void Enemy::SubHP(int damage)
{
	HP -= damage;
}

int Enemy::GetHP()
{
	return HP;
}
