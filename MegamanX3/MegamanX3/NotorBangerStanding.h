#include "NotorBangerState.h"

class NotorBangerStanding : public NotorBangerState
{
public:
	NotorBangerStanding(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerStanding();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};
