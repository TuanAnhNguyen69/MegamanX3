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

void Enemy::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::MegamanBullet_ID)
	{
		if (this->GetHP() > 0 && !((PlayerBullet*) impactor)->IsHitted()) {
			this->SubHP(((PlayerBullet*)impactor)->GetDamage());
		}
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
