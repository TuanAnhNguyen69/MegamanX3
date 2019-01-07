#include "pch.h"
#include "BlastHornetFly.h"


BlastHornetFly::BlastHornetFly(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(30, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		0, 2, 6, 100, 100);
}


BlastHornetFly::~BlastHornetFly()
{
	if (handler->GetCurrentStateName() != BlastHornetStateHandler::StateName::Fly) {
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void BlastHornetFly::Load()
{
	route = BlastHornetFly::Unknow;
	entity->SetSprite(sprite);

	startPoint = entity->GetPosition();
	intersectionPoint = D3DXVECTOR3(handler->GetPointA().x - 200, handler->GetPointA().y + 50, 0);

	point1 = D3DXVECTOR3(intersectionPoint.x - 150, intersectionPoint.y + 100, 0);
	point2 = D3DXVECTOR3(intersectionPoint.x - 150, intersectionPoint.y - 100, 0);
	point3 = D3DXVECTOR3(intersectionPoint.x + 150, intersectionPoint.y + 100, 0);
	point4 = D3DXVECTOR3(intersectionPoint.x + 150, intersectionPoint.y - 100, 0);

	timeStartState = clock();

	hadDrop = false;
}

void BlastHornetFly::Update()
{
	BlastHornetState::Update();
	if (entity->GetPosition() == intersectionPoint)
	{
		route = BlastHornetFly::AtIntersection;
	}
	if (entity->GetPosition() == point1)
	{
		entity->SetReverse(true);
		route = BlastHornetFly::AtPoint1;
	}
	if (entity->GetPosition() == point2)
	{
		route = BlastHornetFly::AtPoint2;
	}
	if (entity->GetPosition() == point3)
	{
		entity->SetReverse(false);
		route = BlastHornetFly::AtPoint3;
	}
	if (entity->GetPosition() == point4)
	{
		route = BlastHornetFly::AtPoint4;
	}

	switch (route)
	{
	case BlastHornetFly::Unknow:
		entity->GoTo(startPoint, intersectionPoint, Define::BLASTHORNET_RETURN_SPEED);
		break;
	case BlastHornetFly::AtIntersection:
		entity->GoTo(intersectionPoint, point1, Define::BLASTHORNET_FLY_SPEED);
		break;
	case BlastHornetFly::AtPoint1:
		entity->GoTo(point1, point2, Define::BLASTHORNET_FLY_SPEED);
		break;
	case BlastHornetFly::AtPoint2:
		entity->GoTo(point2, point3, Define::BLASTHORNET_FLY_SPEED);
		break;
	case BlastHornetFly::AtPoint3:
		entity->GoTo(point3, point4, Define::BLASTHORNET_FLY_SPEED);
		break;
	case BlastHornetFly::AtPoint4:
		entity->GoTo(point4, point1, Define::BLASTHORNET_FLY_SPEED);
		break;
	}

	timeCount = clock();
	int dt = (timeCount - timeStartState) / 1000;

	if (dt % 4 != 0)
	{
		hadDrop = true;
	}

	if(dt % 4 == 0 && dt > 0 && hadDrop)
	{
		Bee *bee = new Bee(handler->GetPlayer());
		bee->SetPosition(entity->GetPosition().x, entity->GetPosition().y);
		bee->SetScale(2, 2);
		bee->SetBound(15, 15);
		bee->Initailize();
		EntityManager::GetInstance()->AddEntity(bee);
		hadDrop = false;
	}
}

void BlastHornetFly::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
