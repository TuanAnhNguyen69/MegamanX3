#include "pch.h"
#include "HelitShooting.h"
#include "HelitRocket.h"
#include "Roof.h"


HelitShooting::HelitShooting(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit",
		0, 4, 5, 50, 50);
}

HelitShooting::~HelitShooting()
{
	if (handler->GetCurrentStateName() != HelitStateHandler::StateName::Shooting) 
	{
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HelitShooting::Load()
{
	/*startState = clock();*/
	hadShoot = false;
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
	hadShoot = false;
	ammo = 2;
}

void HelitShooting::Update()
{	

	if (!handler->GetLeftTarget())
	{
		entity->SetReverse(true);
		if (!handler->GetAboveTarget()) {
			entity->AddVelocityY(10.0f);
		}
		else {
			entity->AddVelocityY(-10.0f);
			if (ammo > 0) {
				if (sprite->GetCurrentFrame() == 1) {
					if (!hadShoot) {
						HelitRocket *rocket = new HelitRocket(((Enemy*)entity)->player);
						rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y + 22);
						rocket->Initialize(handler->GetLeftTarget());
						rocket->SetScale(2, 2);
						rocket->SetBound(16, 12);
						EntityManager::GetInstance()->AddEntity(rocket);
						Sound::getInstance()->loadSound((char*)"sound/shoot_rocket.wav", "rocket_helit");
						Sound::getInstance()->play("rocket_helit", false, 1);
						hadShoot = true;
						ammo--;
					}
				}
				else {
					hadShoot = false;
				}

			}
			else {
				handler->SetHadShootState(true);
				handler->ChangeState(HelitStateHandler::StateName::Flying);
			}
		}
	}
	else {
		entity->SetReverse(false);
		if (!handler->GetAboveTarget()) {
			entity->AddVelocityY(10.0f);
		}
		else {
			entity->AddVelocityY(-10.0f);
			if (ammo > 0) {
				if (sprite->GetCurrentFrame() == 1) {
					if (!hadShoot) {
						HelitRocket *rocket = new HelitRocket(((Enemy*)entity)->player);
						rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y + 22);
						rocket->Initialize(handler->GetLeftTarget());
						rocket->SetScale(2, 2);
						rocket->SetBound(16, 12);
						EntityManager::GetInstance()->AddEntity(rocket);
						hadShoot = true;
						ammo--;
					}
				}
				else {
					hadShoot = false;
				}

			}
			else {
				handler->SetHadShootState(true);
				handler->ChangeState(HelitStateHandler::StateName::Flying);
			}
		}
	}

	//int dt = 0;
	//	/*clock_t count = clock();
	//	dt = (count - startState);
	//	if ((dt % 800 > 600 ))
	//	{
	//		if (!hadShoot) 
	//		{
	//			HelitRocket *rocket = new HelitRocket();
	//			rocket->SetPosition(entity->GetPosition().x, entity->GetPosition().y + 22);
	//			rocket->Initialize(handler->GetLeftTarget());
	//			rocket->SetScale(2, 2);
	//			rocket->SetBound(16, 12);
	//			EntityManager::GetInstance()->AddEntity(rocket);
	//			hadShoot = true;
	//			ammo --;
	//		}
	//	}
	//	else {
	//		hadShoot = false;
	//	}*/	
	
}

void HelitShooting::OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID
		|| impactor->GetEntityId() == EntityId::Megaman_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			break;
		}

		case Entity::Right:
		{
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{

			/*entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top + 1);
			entity->SetVelocity(0, 0);	*/
			entity->AddVelocityY(+20.0f);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{

			entity->AddVelocityY(-20.0f);
			break;
		}
		}
	}

	if (impactor->GetEntityId() == EntityId::Roof_ID)
	{
		switch (side)
		{

		case Entity::Left:
		{
			break;
		}

		case Entity::Right:
		{
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{

			/*entity->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top + 1);
			entity->SetVelocity(0, 0);	*/
			entity->AddVelocityY(+20.0f);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			entity->SetPosition(entity->GetPosition().x, ((Roof *)impactor)->GetCollidePosition(entity) - entity->GetWidth() / 2);
			entity->AddVelocityY(-20.0f);
			break;
		}
		}
	}
}
