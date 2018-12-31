#include "pch.h"
#include "BlastHornetReturn.h"


BlastHornetReturn::BlastHornetReturn(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(30, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		0, 2, 6, 100, 100);
}


BlastHornetReturn::~BlastHornetReturn()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Prepare) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetReturn::Load()
{
	entity->SetSprite(sprite);
	curPos = D3DXVECTOR3(entity->GetPosition().x, entity->GetPosition().y, 0);
}

void BlastHornetReturn::Update()
{
	//Nếu BlastHornet trở về A
	if (isGoToPointA)
	{
		//Nếu đã ở A thì chuyển sang State Prepare
		if (entity->GetPosition().x == handler->GetPointA().x && entity->GetPosition().y == handler->GetPointA().y)
		{
			handler->ChangeState(BlastHornetStateHandler::StateName::Prepare);
		}
		//Nếu chưa ở A
		else
		{
			//Vector vận tốc sẽ hướng từ curPos về A
			//Vector có phương, chiều (x/y,y/x) ~ (x,y)
			//x = xA - xCurrent, y = yA - yCurrent, y luôn âm
			//Vector có độ lớn như Define
			entity->SetVelocity(
				(handler->GetPointA().x - curPos.x) / abs(handler->GetPointA().y - curPos.y) * Define::BLASTHORNET_RETURN_SPEED_X,
				(handler->GetPointA().y - curPos.y) / (handler->GetPointA().x - curPos.x) * Define::BLASTHORNET_RETURN_SPEED_Y);
		}
	}
	//Nếu BlastHornet trở về B
	else
	{
		//Nếu đã ở B thì chuyển sang State Prepare
		if (entity->GetPosition().x == handler->GetPointB().x && entity->GetPosition().y == handler->GetPointB().y)
		{
			handler->ChangeState(BlastHornetStateHandler::StateName::Prepare);
		}
		//Nếu chưa ở B
		else
		{
			//Vector vận tốc sẽ hướng từ curPos về B
			//Vector có phương (x/y,y/x) ~ (x,y)
			//x = xB - xCurrent, y = yB - yCurrent, y luôn âm
			//Vector có độ lớn như Define
			entity->SetVelocity(
				(handler->GetPointB().x - curPos.x) / abs(handler->GetPointA().y - curPos.y) * Define::BLASTHORNET_RETURN_SPEED_X,
				(handler->GetPointB().y - curPos.y) / (handler->GetPointB().x - curPos.x) * Define::BLASTHORNET_RETURN_SPEED_Y);
		}
	}
}

void BlastHornetReturn::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
