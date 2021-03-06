#include "pch.h"
#include "HelitFlying.h"
#include "Roof.h"


HelitFlying::HelitFlying(HelitStateHandler *handler, Entity *entity) : HelitState(handler, entity)
{
	sprite = new AnimatedSprite(15, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "helit",
		0, 4, 5, 50, 50);
	
}
HelitFlying::~HelitFlying()
{
	if (handler->GetCurrentStateName() != HelitStateHandler::StateName::Flying) 
	{
		if (sprite) {
			delete sprite;
			sprite = nullptr;
		}
	}
}

void HelitFlying::Load()
{
	entity->SetSprite(sprite);
	entity->SetVelocity(0, 0);
}

void HelitFlying::Update()
{
	if (handler->GetHadShootState()) {
		entity->AddVelocityY(-10.0f);
	}
	else {
		if (!handler->GetLeftTarget())
		{
			entity->SetReverse(true);
			if (!handler->GetAboveTarget()) {
				entity->AddVelocityY(10.0f);
			}
			else {
				entity->AddVelocityY(-10.0f);
				handler->ChangeState(HelitStateHandler::StateName::Shooting);
			}
		}
		else {
			entity->SetReverse(false);
			if (!handler->GetAboveTarget()) {
				entity->AddVelocityY(10.0f);
			}
			else {
				entity->AddVelocityY(-10.0f);
				handler->ChangeState(HelitStateHandler::StateName::Shooting);

			}
		}
	}


}

void HelitFlying::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
	if (impactor->GetEntityId() == EntityId::Platform_ID 
		|| impactor->GetEntityId() == EntityId::Megaman_ID )
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

	if ( impactor->GetEntityId() == EntityId::Roof_ID)
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
