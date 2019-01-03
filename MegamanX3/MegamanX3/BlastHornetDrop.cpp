#include "pch.h"
#include "BlastHornetDrop.h"


BlastHornetDrop::BlastHornetDrop(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(15, 0.5, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		24, 35, 6, 100, 100);
}


BlastHornetDrop::~BlastHornetDrop()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Drop) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetDrop::Load()
{
	handler->SetPreAction(BlastHornetStateHandler::StateName::Drop);
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadDrop = false;
	targetPos = handler->GetPlayerPos();
}

void BlastHornetDrop::Update()
{
	if (sprite->GetCurrentFrame() == 10 && !hadDrop)
	{
		Bee *bee1, *bee2, *bee3, *bee4, *bee5;
		bee1 = new Bee(D3DXVECTOR3(targetPos.x + 1000, targetPos.y, 0));
		bee2 = new Bee(D3DXVECTOR3(targetPos.x + 500, targetPos.y, 0));
		bee3 = new Bee(targetPos);
		bee4 = new Bee(D3DXVECTOR3(targetPos.x - 500, targetPos.y, 0));
		bee5 = new Bee(D3DXVECTOR3(targetPos.x - 1000, targetPos.y, 0));

		bee1->SetPosition(entity->GetPosition().x, entity->GetPosition().y);
		bee2->SetPosition(entity->GetPosition().x, entity->GetPosition().y);
		bee3->SetPosition(entity->GetPosition().x, entity->GetPosition().y);
		bee4->SetPosition(entity->GetPosition().x, entity->GetPosition().y);
		bee5->SetPosition(entity->GetPosition().x, entity->GetPosition().y);

		bee1->SetScale(2, 2);
		bee2->SetScale(2, 2);
		bee3->SetScale(2, 2);
		bee4->SetScale(2, 2);
		bee5->SetScale(2, 2);

		bee1->SetBound(15 * 2, 15 * 2);
		bee2->SetBound(15 * 2, 15 * 2);
		bee3->SetBound(15 * 2, 15 * 2);
		bee4->SetBound(15 * 2, 15 * 2);
		bee5->SetBound(15 * 2, 15 * 2);

		EntityManager::GetInstance()->AddEntity(bee1);
		EntityManager::GetInstance()->AddEntity(bee2);
		EntityManager::GetInstance()->AddEntity(bee3);
		EntityManager::GetInstance()->AddEntity(bee4);
		EntityManager::GetInstance()->AddEntity(bee5);
		hadDrop = true;
	}

	if (sprite->IsFinished())
	{
		sprite->ResetFrame();
		handler->ChangeState(BlastHornetStateHandler::StateName::Return);
	}
}

void BlastHornetDrop::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
