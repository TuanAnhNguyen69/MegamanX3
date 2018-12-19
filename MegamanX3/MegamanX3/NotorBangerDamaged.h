#include "NotorBangerState.h"

class NotorBangerDamaged : public NotorBangerState
{
public:
	NotorBangerDamaged(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerDamaged();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);
};