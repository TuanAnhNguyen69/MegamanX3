#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(EntityId entityId, Player * player) : Entity(entityId)
{
	this->player = player;
	this->active = false;
	this->activeRange = 0;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (GetPlayerDistance() < activeRange) {
		active = true;
	}
	else {
		active = false;
	}

	if (active) {
		Entity::Update();
	}
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

bool Enemy::IsActive()
{
	return active;
}

void Enemy::SetActive(bool active)
{
	this->active = active;
}

void Enemy::SetActiveRange(int activeRange)
{
	this->activeRange = activeRange;
}

void Enemy::SubHP(int damage)
{
	HP -= damage;
}

int Enemy::GetHP()
{
	return HP;
}

int Enemy::GetPlayerDistance()
{
	int xDistance = player->GetPosition().x - this->GetPosition().x;
	int yDistance = player->GetPosition().y - this->GetPosition().y;
	return sqrt(xDistance * xDistance + yDistance * yDistance);
}
