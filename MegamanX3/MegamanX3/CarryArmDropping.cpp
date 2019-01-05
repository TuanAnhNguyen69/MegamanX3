#include "pch.h"
#include "CarryArmDropping.h"
//#include "CarryArmRocket.h"


CarryArmDropping::CarryArmDropping(CarryArmStateHandler *handler, Entity *entity) : CarryArmState(handler, entity)
{
	sprite = new AnimatedSprite(20, 0.3, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "carry_arm",
		6, 11, 6, 50, 65);
}

CarryArmDropping::~CarryArmDropping()
{
	if (handler->GetCurrentStateName() != CarryArmStateHandler::StateName::Dropping) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void CarryArmDropping::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	handler->SetHadDropState(true);

	

	/*handler->box = new Box();
	handler->box->Initialize(false);
	handler->box->SetPosition(entity->GetPosition().x, entity->GetPosition().y + 57);
	handler->box->SetScale(2, 2);
	handler->box->SetBound(50 * 2, 50 * 2);
	EntityManager::GetInstance()->AddEntity(handler->box);*/
}

void CarryArmDropping::Update()
{
	
	if (!sprite->IsFinished()) {
		if (sprite->GetCurrentFrame() == 2) {
			//handler->box->SetVelocity(entity->GetVelocity().x, entity->GetVelocity().y);
			handler->box->SetFall(true);
 		}

		//CarryArmRocket *rocket = new CarryArmRocket();
		/*rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y + 22);
		rocket->Initialize(handler->GetLeftTarget());
		rocket->SetScale(2, 2);
		rocket->SetBound(16, 12);
		EntityManager::GetInstance()->AddEntity(rocket);
		hadShoot = true;*/
		
	}		
	else {
		handler->ChangeState(CarryArmStateHandler::StateName::Flying);
	}

}

void CarryArmDropping::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
