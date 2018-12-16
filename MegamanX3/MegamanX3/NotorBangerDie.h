#include "NotorBangerState.h"

class NotorBangerDie : public NotorBangerState
{
public:
	NotorBangerDie(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerDie();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};