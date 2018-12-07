#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "NotorBangerStateHandler.h"
#include "Engine.h"
#include <iostream>

class NotorBangerState
{
public:
	NotorBangerState(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	NotorBangerStateHandler *handler;
	Entity *entity;
};

class NotorBangerStanding : public NotorBangerState
{
public:
	NotorBangerStanding(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerStanding();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

class NotorBangerFire : public NotorBangerState
{
public:
	NotorBangerFire(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerFire();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

class NotorBangerJump : public NotorBangerState
{
public:
	NotorBangerJump(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerJump();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

class NotorBangerDamaged : public NotorBangerState
{
public:
	NotorBangerDamaged(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerDamaged();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

class NotorBangerDie : public NotorBangerState
{
public:
	NotorBangerDie(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerDie();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

