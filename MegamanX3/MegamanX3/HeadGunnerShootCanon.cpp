#include "pch.h"
#include "HeadGunnerShootCanon.h"


HeadGunnerShootCanon::HeadGunnerShootCanon(HeadGunnerStateHandler *handler, Entity *entity) : HeadGunnerState(handler, entity)
{
	sprite = new AnimatedSprite(5, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "head_gunner",
		0, 0, 1, 50, 50);
}


HeadGunnerShootCanon::~HeadGunnerShootCanon()
{
	if (handler->GetCurrentStateName() != HeadGunnerStateHandler::StateName::ShootCanon) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HeadGunnerShootCanon::Load()
{
	isLeft = handler->GetIsLeft();
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;
	entity->SetReverse(!isLeft);
	timeStartState = clock();
}

void HeadGunnerShootCanon::Update()
{
	/*timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;
	if (!hadShoot && dt > 1)*/
	if(!hadShoot)
	{
		Canon *canon = new Canon();
		if(isLeft)
			canon->SetPosition(entity->GetPosition().x + 30, entity->GetPosition().y - 20);
		else
			canon->SetPosition(entity->GetPosition().x - 30, entity->GetPosition().y - 20);
		canon->Initialize(false, isLeft);
		canon->SetScale(2, 2);
		canon->SetBound(9, 9);
		EntityManager::GetInstance()->AddEntity(canon);
		hadShoot = true;
		handler->ChangeState(HeadGunnerStateHandler::StateName::Standing);
	}
}

void HeadGunnerShootCanon::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
