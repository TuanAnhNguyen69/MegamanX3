#include "pch.h"
#include "BlastHornetPrick.h"


BlastHornetPrick::BlastHornetPrick(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(25, 1, false);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		3, 23, 6, 100, 100);
}


BlastHornetPrick::~BlastHornetPrick()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Prepare) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetPrick::Load()
{
	entity->SetVelocity(0, 0);
	entity->SetSprite(sprite);
	targetPos = handler->GetPlayerPos();
}

void BlastHornetPrick::Update()
{
	//Nếu đang ở A
	if (entity->GetPosition().x == handler->GetPointA().x && entity->GetPosition().y == handler->GetPointA().y)
	{
		//Vector vận tốc sẽ hướng từ A tới target
		//Vector có phương, chiều (x/y,y/x) ~ (x,y)
		//x = xA - xCurrent, y = yA - yCurrent, y luôn dương
		//Vector có độ lớn như Define
		entity->SetVelocity(
			(targetPos.x - handler->GetPointA().x) / (targetPos.y - handler->GetPointA().y) * Define::BLASTHORNET_PRICK_SPEED_X,
			(targetPos.y - handler->GetPointA().y) / abs(targetPos.x - handler->GetPointA().x) * Define::BLASTHORNET_PRICK_SPEED_Y
		);
	}
	//Nếu đang ở B
	else
	{
		//Vector vận tốc sẽ hướng từ B tới target
		//Vector có phương, chiều (x/y,y/x) ~ (x,y)
		//x = xB - xCurrent, y = yB - yCurrent, y luôn dương
		//Vector có độ lớn như Define
		entity->SetVelocity(
			(targetPos.x - handler->GetPointA().x) / (targetPos.y - handler->GetPointA().y) * Define::BLASTHORNET_PRICK_SPEED_X,
			(targetPos.y - handler->GetPointA().y) / abs(targetPos.x - handler->GetPointA().x) * Define::BLASTHORNET_PRICK_SPEED_Y
		);
	}
}

void BlastHornetPrick::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			entity->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			entity->SetVelocity(0, 0);
			handler->ChangeState(BlastHornetStateHandler::StateName::Return);
			break;
		}

		case Entity::Right:
		{
			entity->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			entity->SetVelocity(0, 0);
			handler->ChangeState(BlastHornetStateHandler::StateName::Return);
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{
			entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			entity->SetVelocity(0, 0);
			handler->ChangeState(BlastHornetStateHandler::StateName::Return);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			entity->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			entity->SetVelocity(0, 0);
			handler->ChangeState(BlastHornetStateHandler::StateName::Return);
			break;
		}
		}
	}
}
