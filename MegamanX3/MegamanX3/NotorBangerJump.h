#include "NotorBangerState.h"

class NotorBangerJump : public NotorBangerState
{
public:
	NotorBangerJump(NotorBangerStateHandler *handler, Entity *entity);
	~NotorBangerJump();

	void Load();
	void Update();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
private:
	float acceleratorX;
	float acceleratorY;
};