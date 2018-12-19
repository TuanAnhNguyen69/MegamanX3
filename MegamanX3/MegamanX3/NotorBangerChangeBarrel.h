#pragma once
#include "NotorBangerState.h"
class NotorBangerChangeBarrel :
	public NotorBangerState
{
public:
	NotorBangerChangeBarrel(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerChangeBarrel();

	void Load();
	void Update();
	void OnCollision(Entity *impactor,  Entity::CollisionSide side, Entity::CollisionReturn data);
private:
	
	
};

