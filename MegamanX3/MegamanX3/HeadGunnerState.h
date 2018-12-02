#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "HeadGunnerStateHandler.h"
#include "Engine.h"
#include <iostream>

class HeadGunnerState
{
public:
	HeadGunnerState(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerState();

	virtual void Load();
	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
	AnimatedSprite * sprite;
	HeadGunnerStateHandler *handler;
	Entity *entity;
};

class HeadGunnerStanding : public HeadGunnerState
{
public:
	HeadGunnerStanding(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerStanding();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

class HeadGunnerFire : public HeadGunnerState
{
public:
	HeadGunnerFire(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerFire();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


class HeadGunnerDamaged : public HeadGunnerState
{
public:
	HeadGunnerDamaged(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerDamaged();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

class HeadGunnerDie : public HeadGunnerState
{
public:
	HeadGunnerDie(HeadGunnerStateHandler *handler, Entity *entity);
	~HeadGunnerDie();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

